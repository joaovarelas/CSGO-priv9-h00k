#include "SDK.h"

//junk code 4 vacation
struct st0s0t00s0s0t00s0t0s0t0s0 {
	bool vac = (bool)0;
};
class cl0lccclcl00clc00lc0lc0lc {
public:
	float x;
	float y;
	float z;
	bool vac;
};


cl0lccclcl00clc00lc0lc0lc vacavacavacv;

extern Interfaces::Engine* Engine;
extern Interfaces::IEngineTrace* EngineTrace;
extern Interfaces::CVar* cVar;
extern Interfaces::EntityList* EntList;
extern Interfaces::Surface* Surface;


extern Interfaces::CGlobalVars* pGlobalVars;
extern Interfaces::IGameMovement* pGameMovement;
extern Interfaces::IMoveHelper* pMoveHelper;
extern Interfaces::IPrediction* pPrediction;


int* pPredSeed;


typedef void(__thiscall* SetHost_t)(void*, void*);
float m_flOldCurtime;
float m_flOldFrametime;
MoveData data;





void Hacks::Prediction::Start(CUserCmd* cmd)
{
	if (!Settings::Prediction)
		return;

	BaseEntity * Local = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());
	if (!Local)
		return;

	*pPredSeed = cmd->command_number;

	m_flOldCurtime = pGlobalVars->frametime;
	m_flOldFrametime = pGlobalVars->curtime;

	pGlobalVars->frametime = pGlobalVars->interval_per_tick;
	pGlobalVars->curtime = Local->GetTickBase() * pGlobalVars->interval_per_tick;

	pGameMovement->StartTrackPredictionErrors(Local);

	memset(&data, 0, sizeof(MoveData));

	pMoveHelper->SetHost(Local);
	pPrediction->SetupMove(Local, cmd, pMoveHelper, &data);
	pGameMovement->ProcessMovement(Local, &data);
	pPrediction->FinishMove(Local, cmd, &data);

}


void Hacks::Prediction::End()
{
	if (!Settings::Prediction)
		return;

	BaseEntity * Local = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());
	if (!Local)
		return;

	pGameMovement->FinishTrackPredictionErrors(Local);
	pMoveHelper->SetHost(nullptr);

	*pPredSeed = -1;

	pGlobalVars->curtime = m_flOldCurtime;
	pGlobalVars->frametime = m_flOldFrametime;
}



void Hacks::ChangeName(const char* name) {

	// Name Change	
	Interfaces::ConVar* Name = cVar->FindVar("name");
	*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = NULL;
	Name->SetValue(name);
}

void Hacks::Radar(BaseEntity* pEntity) {
	if (!Settings::Radar)
		return;

	BaseEntity* LocalPlayer = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());

	// Radar
	if (!pEntity->IsSpotted() && (pEntity->GetTeam() != LocalPlayer->GetTeam()))
		*(bool*)((DWORD)pEntity + 0x939) = true;

}

void Hacks::Airstuck(CUserCmd* cmd) {
	//airstuck
	if (GetAsyncKeyState(VK_NUMLOCK) && Settings::AirStuck)
		cmd->tick_count = 16777216;

}

void Hacks::Bhop(CUserCmd* cmd, BaseEntity* LocalPlayer) {
	// Bhop
	if ((Settings::BunnyHop) && cmd->buttons & IN_JUMP && !(LocalPlayer->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}

void Hacks::Autostop(CUserCmd* cmd) {
	if (!Settings::AutoStop)
		return;


	cmd->forwardmove = 0;
	cmd->sidemove = 0;
	cmd->upmove = 0;
	//cmd->buttons = 0;
}

void Hacks::Triggerbot(CUserCmd* cmd, BaseEntity* LocalPlayer) {
	// Triggerbot
	if (GetAsyncKeyState(VK_MENU) && Settings::Triggerbot) //ALT key
	{
		int cross = LocalPlayer->InCross();
		if (cross > 0 && cross <= 64)
		{
			BaseEntity* target = (BaseEntity*)EntList->GetClientEntity(cross);
			if (!target->IsDormant() && target->GetTeam() != LocalPlayer->GetTeam())
				cmd->buttons |= IN_ATTACK;
		}
	}

}

float GetRealDistanceFOV(float distance, QAngle angle, CUserCmd* cmd)
{
	/*    n
	w + e
	s        'real distance'
	|
	a point -> x --..  v
	|     ''-- x <- a guy
	|          /
	|         /
	|       /
	| <------------ both of these lines are the same length
	|    /      /
	|   / <-----'
	| /
	o
	localplayer
	*/

	Vector aimingAt;
	Math::AngleVectors(cmd->viewangles, aimingAt);
	aimingAt.x *= distance;
	aimingAt.y *= distance;
	aimingAt.z *= distance;

	Vector aimAt;
	Math::AngleVectors(angle, aimAt);
	aimAt.x *= distance;
	aimAt.y *= distance;
	aimAt.z *= distance;

	return (aimAt - aimingAt).Length2D();
}

bool Hacks::IsVisible(BaseEntity* target, int bone) {

	BaseEntity* LocalPlayer = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());

	Ray_t ray;
	trace_t tr;
	ray.Init(LocalPlayer->GetEyePos(), target->GetBonePosition(bone));

	CTraceFilter filter;
	filter.pSkip = LocalPlayer;
	EngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	return (tr.m_pEnt == target);
}

void Hacks::NoRecoil(CUserCmd* cmd, BaseEntity* LocalPlayer) {
	//norecoil

	if (!Settings::NoRecoil)
		return;

	QAngle ang = LocalPlayer->GetPunchAngles();
	cmd->viewangles.x -= ang.x * 2.f;
	cmd->viewangles.y -= ang.y * 2.f;

}


static bool isShooting = false;
void __fastcall Hacks::Aimbot(CUserCmd* cmd, BaseEntity* LocalPlayer, bool& bSendPacket) {

	if (!Settings::Aimbot)
		return;




	//Aimbot
	float Fov = Settings::FOV;
	float bestFov = Fov;
	float bestRealDistance = Fov * 10.f;
	float bestDistance = FLT_MAX;
	int nTarget = -1;

	for (int i = 1; i <= Engine->GetMaxClients(); i++)// EntityList->GetHighestEntityIndex()
	{
		BaseEntity* pEntity = (BaseEntity*)EntList->GetClientEntity(i);

		if (!pEntity->IsValid())
			continue;

		if ((pEntity->GetTeam() == LocalPlayer->GetTeam()) && !Settings::AimTeam)
			continue;


		if (!IsVisible(pEntity, Settings::AimBone))
			continue;

		//Resolve!?
		//pEntity->GetAbsAngles().y = *pEntity->GetLowerBodyYaw();


		Vector LocalEyePos = LocalPlayer->GetEyePos();
		Vector pEntityHead = pEntity->GetBonePosition(Settings::AimBone);//8 head

		float distance = (pEntityHead - LocalEyePos).Length();
		float fov = Math::GetFov(cmd->viewangles, Math::CalcAngle(pEntityHead - LocalEyePos));
		float real_distance = GetRealDistanceFOV(distance, Math::CalcAngle(pEntityHead - LocalEyePos), cmd);


		if (distance > bestDistance)
			continue;

		if (fov > bestFov)
			continue;

		//if (real_distance > bestRealDistance)
			//continue;

		nTarget = i;
		bestFov = fov;
		bestRealDistance = real_distance;
		bestDistance = distance;

	}




	if (Settings::AutoRevolver) {
		//autorevolver
		static int delay = 0;
		delay++;

		if (delay <= 15) {


			cmd->buttons |= IN_ATTACK;
		}
		else {
			delay = 0;
		}

	}



	QAngle oldAngle;
	Engine->GetViewAngles(oldAngle);


	if (nTarget != -1) {

		if (Settings::AimKey && !(cmd->buttons & IN_ATTACK))
			return;


		BaseEntity* pEntity = (BaseEntity*)EntList->GetClientEntity(nTarget);
		QAngle aimAngle = Math::CalcAngle(pEntity->GetBonePosition(Settings::AimBone) - LocalPlayer->GetEyePos());



		Math::ClampViewAngles(aimAngle);


		Hacks::Autostop(cmd);
		
		//Set angles
		if (Settings::AimSilent)
			cmd->viewangles = aimAngle;
		else
			Engine->SetViewAngles(aimAngle);
			
		
		//autoshoot & delay
		static int bullets = 0;
		if (Settings::AutoShoot)
		{


			if (Settings::ShootDelay > 0) {

				bullets++;

				if (bullets >= Settings::ShootDelay) {

					cmd->buttons |= IN_ATTACK;
					bullets = 0;
				}
			}
			else
				cmd->buttons |= IN_ATTACK;
		}

	}//end target


}



void __fastcall Hacks::ESP() {
	BaseEntity* LocalPlayer = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());
	if (!LocalPlayer)
		return;

	if (LocalPlayer->IsDormant())
		return;

	if (LocalPlayer->GetTeam() != 2 && LocalPlayer->GetTeam() != 3)
		return;

	if (!LocalPlayer->IsPlayer())
		return;


	for (int i = 1; i <= Engine->GetMaxClients(); i++)
	{// EntityList->GetHighestEntityIndex()
		BaseEntity* pEntity = (BaseEntity*)EntList->GetClientEntity(i);

		if (pEntity == LocalPlayer)
			continue;

		if (!pEntity->IsValid())
			continue;

		if (pEntity->GetTeam() == LocalPlayer->GetTeam())
			continue;

		Hacks::Radar(pEntity);


		Vector max = pEntity->GetCollideable()->OBBMaxs();

		Vector pos, pos3D;
		Vector top, top3D;
		pos3D = pEntity->GetOrigin();
		top3D = pos3D + Vector(0, 0, max.z);
		if (!Math::WorldToScreen(pos3D, pos) || !Math::WorldToScreen(top3D, top))
			return;


		float height = (pos.y - top.y);
		float width = height / 4.f;


		//Visible color
		Surface->DrawSetColor(IsVisible(pEntity, Settings::AimBone) ? (pEntity->GetTeam() == 2 ? Color::Orange() : Color::Green() ) : (pEntity->GetTeam() == 2 ? Color::Red() : Color::Blue()));


		//BOX
		if (Settings::EspBox == 1) {	 //2D BOX
			Surface->DrawOutlinedRect(top.x - width, top.y, top.x + width, top.y + height);
		}
		else if (Settings::EspBox == 2) { //3D BOX

			Vector vOrigin = pEntity->GetOrigin();
			Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
			Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;

			Vector points[] = { Vector(min.x, min.y, min.z),
				Vector(min.x, max.y, min.z),
				Vector(max.x, max.y, min.z),
				Vector(max.x, min.y, min.z),
				Vector(min.x, min.y, max.z),
				Vector(min.x, max.y, max.z),
				Vector(max.x, max.y, max.z),
				Vector(max.x, min.y, max.z) };

			int edges[12][2] = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },
			{ 4, 5 },{ 5, 6 },{ 6, 7 },{ 7, 4 },
			{ 0, 4 },{ 1, 5 },{ 2, 6 },{ 3, 7 }, };

			for (auto it : edges)
			{
				Vector p1, p2;
				if (!Math::WorldToScreen(points[it[0]], p1) || !Math::WorldToScreen(points[it[1]], p2))
					return;

				Surface->DrawLine(p1.x, p1.y, p2.x, p2.y);
			}
		}




		//Name esp
		if (Settings::EspName) {
			player_info_t pInfo;
			Engine->GetPlayerInfo(i, &pInfo);
			Menu::DrawString(hfont, top.x, top.y - 6, Color::White(), FONT_CENTER, "%s", pInfo.name);
		}


		//HP
		if (Settings::EspHealth)
			Menu::DrawString(hfont, top.x, top.y + height + 6, Color::White(), FONT_CENTER, "%d", pEntity->GetHealth());

	}

}



void Hacks::CorrectMovement(QAngle vOldAngles, CUserCmd* cmd, float fOldForward, float fOldSidemove)
{
	// side/forward move correction
	float deltaView;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (cmd->viewangles.y < 0.0f)
		f2 = 360.0f + cmd->viewangles.y;
	else
		f2 = cmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;

	cmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	cmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;


}