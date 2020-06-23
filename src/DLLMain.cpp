#include "SDK.h"


//junk code 4 vacation
struct st0t0t0t0v {
	bool vac = (bool)0;
};
class cllclcllint {
public:
	float x;
	float y;
	float z;
	bool vac;
};
void __fastcall vfvf0fv0f00f0() {

	cllclcllint c00c0c00c0c000c0c00c;
	c00c0c00c0c000c0c00c.x = FLT_MAX;
	c00c0c00c0c000c0c00c.y = c00c0c00c0c000c0c00c.x;
	c00c0c00c0c000c0c00c.x = c00c0c00c0c000c0c00c.y;
	c00c0c00c0c000c0c00c.z = FLT_MAX;
	c00c0c00c0c000c0c00c.y = c00c0c00c0c000c0c00c.z;

	cllclcllint* c00c0c00c0c000c0c00c1 = new cllclcllint;
	cllclcllint* c00c0c00c0c000c0c00c2 = new cllclcllint;
	cllclcllint* c00c0c00c0c000c0c00c3 = new cllclcllint;
	

	int ffsfffsfffsfffsfffsffsf = 13123213;
	DWORD kakwdiwhccxxxaddaaxasfgojdwadawdwa = 0;
	long euihejogsguis5h545jadwadwaduiwahdiwad;
	euihejogsguis5h545jadwadwaduiwahdiwad = 0;
	ffsfffsfffsfffsfffsffsf = ffsfffsfffsfffsfffsffsf + 1;
	ffsfffsfffsfffsfffsffsf += 1;
	ffsfffsfffsfffsfffsffsf *= 1;
	ffsfffsfffsfffsfffsffsf = ffsfffsfffsfffsfffsffsf;
	bool test = true;
	bool* troll = &(test);

	delete c00c0c00c0c000c0c00c1;
	delete c00c0c00c0c000c0c00c2;
	delete c00c0c00c0c000c0c00c3;


}
inline bool __stdcall bbstb0s0t0b0d00t() {

	int itnitintintititntni = 13123213;
	DWORD kakwdiwadggh566775636ggdaaxasfgojdwadawdwa = 0;
	long ldlododdn;
	ldlododdn = 0;

	bool test = true;
	bool* troll = &(test);
	itnitintintititntni = 1;
	itnitintintititntni = 2;
	itnitintintititntni = 3;
	itnitintintititntni = 1337;
	kakwdiwadggh566775636ggdaaxasfgojdwadawdwa = 0;
	static bool testt = test;
	test = !testt;
	return test;
}
inline void __stdcall iviinfldine() {

	int itnitintintititntni = 13123213;
	DWORD kakwdiwadggh566775636ggdaaxasfgojdwadawdwa = 0;
	long ldlododdn;
	ldlododdn = 0;
	bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t(); vfvf0fv0f00f0();


	bool test = true;
	bool* troll = &(test);
	itnitintintititntni = 1;
	itnitintintititntni = 1337;
	kakwdiwadggh566775636ggdaaxasfgojdwadawdwa = 0;
	static bool testt = test;
	test = !testt;

}








inline bool Compare(const uint8_t* data, const uint8_t* pattern, const char* mask) {
	for (; *mask; ++mask, ++data, ++pattern)
		if (*mask == 'x' && *data != *pattern)
			return false;

	return (*mask) == 0;
}

uintptr_t FindPattern(const char* module, const char* pattern_string, const char* mask) {
	MODULEINFO module_info = {};
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(module), &module_info, sizeof MODULEINFO);

	uintptr_t module_start = uintptr_t(module_info.lpBaseOfDll);

	const uint8_t* pattern = reinterpret_cast<const uint8_t*>(pattern_string);

	for (size_t i = 0; i < module_info.SizeOfImage; i++)
		if (Compare(reinterpret_cast<uint8_t*>(module_start + i), pattern, mask))
			return module_start + i;

	return 0;
}



//Interfaces
Interface::InterfaceTools* newInterface = new Interface::InterfaceTools;

Interfaces::Engine* Engine = (Interfaces::Engine*)newInterface->GetInterface("engine.dll", "VEngineClient014");
Interfaces::EntityList* EntList = (Interfaces::EntityList*)newInterface->GetInterface("client.dll", "VClientEntityList003");;
Interfaces::IEngineTrace* EngineTrace = (Interfaces::IEngineTrace*)newInterface->GetInterface("engine.dll", "EngineTraceClient004");;
Interfaces::Panel* Panel = (Interfaces::Panel*)newInterface->GetInterface("vgui2.dll", "VGUI_Panel009");
Interfaces::Surface* Surface = (Interfaces::Surface*)newInterface->GetInterface("vguimatsurface.dll", "VGUI_Surface031");
Interfaces::CVar* cVar = (Interfaces::CVar*)newInterface->GetInterface("materialsystem.dll", "VEngineCvar007");
Interfaces::BaseClientDLL* baseClientDLL = (Interfaces::BaseClientDLL*)newInterface->GetInterface("client.dll", "VClient018");
Interfaces::IGameMovement* pGameMovement = (Interfaces::IGameMovement*)newInterface->GetInterface("client.dll", "GameMovement001");
Interfaces::IPrediction* pPrediction = (Interfaces::IPrediction*)newInterface->GetInterface("client.dll", "VClientPrediction001");
Interfaces::IMoveHelper* pMoveHelper = **(Interfaces::IMoveHelper***)(FindPattern("client.dll", "\x8B\x0D\x00\x00\x00\x00\x8B\x45\x00\x51\x8B\xD4\x89\x02\x8B\x01", "xx????xx?xxxxxxx") + 2);

Interfaces::ClientMode* clientMode = **(Interfaces::ClientMode***)((*(DWORD**)baseClientDLL)[10] + 0x5);
Interfaces::CInput* Input = **(Interfaces::CInput***)((*(DWORD**)baseClientDLL)[15] + 0x1);
Interfaces::CGlobalVars* pGlobalVars = **(Interfaces::CGlobalVars***)((*(DWORD**)baseClientDLL)[0] + 0x1B);





//VMTables
CVMTHookManager* clientModeVMT;
CVMTHookManager* paintTraverseVMT;
CVMTHookManager* baseClientDLLVMT;
//CVMTHookManager* overrideViewVMT;




//Func Hooks
Hooks::oCreateMove createMoveHook;
Hooks::oPaintTraverse paintTraverseHook;
Hooks::oFrameStageNotify frameStageNotifyHook;
//Hooks::oOverrideView overrideViewHook;



//Externals
float Settings::Aimbot;
float Settings::FOV;
float Settings::AimBone;
float Settings::AimTeam;
float Settings::AimSilent;
float Settings::AimKey;
float Settings::AutoShoot;
float Settings::AutoPistol;
float Settings::ShootDelay;


float Settings::NoRecoil;
float Settings::NoVisRecoil;
float Settings::Triggerbot;

float Settings::EspBox;
float Settings::EspName;
float Settings::EspHealth;
float Settings::Radar;

float Settings::AutoRevolver;
float Settings::BunnyHop;
float Settings::AirStuck;
float Settings::AutoStop;
float Settings::Prediction;

HFont hfont = 0;






//Main Handle
HANDLE MainThread = nullptr;
bool isUnhooking = false;

bool __stdcall CreateMove(float sampleTime, CUserCmd* cmd)
{
	if (isUnhooking)
		return true;



	createMoveHook(clientMode, sampleTime, cmd);

	if (!Engine->IsConnected() || !Engine->IsInGame())
		return true;




	BaseEntity* LocalPlayer = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());

	if (!LocalPlayer || !LocalPlayer->IsValid())
		return true;


	if (!cmd || !cmd->command_number)
		return true;


	

	QAngle oldAngle;
	Engine->GetViewAngles(oldAngle);
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	PVOID pebp;
	__asm mov pebp, ebp;
	bool* pbSendPacket = (bool*)(*(DWORD*)pebp - 0x1C);
	bool& bSendPacket = *pbSendPacket;



	Hacks::Bhop(cmd, LocalPlayer);
	Hacks::Airstuck(cmd);


	Hacks::Prediction::Start(cmd);

	Hacks::Aimbot(cmd, LocalPlayer, bSendPacket);
	Hacks::NoRecoil(cmd, LocalPlayer);
	Hacks::Triggerbot(cmd, LocalPlayer);


	Hacks::Prediction::End();
	

	//Hacks::AntiAim(cmd, bSendPacket);


	if(!Settings::AutoStop)
		Hacks::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

	Math::ClampViewAngles(cmd->viewangles);


	return false;
}


void __stdcall PaintTraverse(int vguiID, bool force, bool allowForcing)
{
	if (isUnhooking)
		return;

	paintTraverseHook(Panel, vguiID, force, allowForcing);


	//Get MatSurfaceSystem panel
	static unsigned int drawPanel;
	if (!drawPanel) {
		const char* panelname = Panel->GetName(vguiID);
		if (panelname[0] == 'M' && panelname[1] == 'a' && panelname[2] == 't')
			drawPanel = vguiID;
	}
	if(vguiID != drawPanel)
		return;



	//Menu render
	static bool menuActive = false;
	if (GetAsyncKeyState(VK_INSERT)) {
		menuActive = !menuActive;
		Sleep(300);
	}



	//draw menu
	if (menuActive)
		Menu::Draw();



	if (!Engine->IsInGame() && !Engine->IsConnected())
		return;

	//wh
	Hacks::ESP();


}


void __stdcall FrameStageNotify(ClientFrameStage_t stage)
{
	if (isUnhooking)
		return;

	QAngle punchOld;
	QAngle vPunchOld;

	QAngle* aimPunch = nullptr;
	QAngle* vPunch = nullptr;

	if (Engine->IsInGame())
	{
		if (stage == FRAME_RENDER_START)
		{
			BaseEntity* LocalPlayer = (BaseEntity*)EntList->GetClientEntity(Engine->GetLocalPlayer());

			if (LocalPlayer->IsValid() && LocalPlayer->IsAlive())

			{
				
				if (Settings::NoVisRecoil) {
					aimPunch = (QAngle*)((DWORD)LocalPlayer + 0x301C);

					vPunch = (QAngle*)((DWORD)LocalPlayer + 0x3010);

					punchOld = *aimPunch;
					vPunchOld = *vPunch;

					*aimPunch = QAngle(0, 0, 0);
					*vPunch = QAngle(0, 0, 0);
				}
				


			}


		}
	}

	frameStageNotifyHook(baseClientDLL, stage);

	if (aimPunch && vPunch && Settings::NoVisRecoil)
	{
		*aimPunch = punchOld;
		*vPunch = vPunchOld;
	}
}


void __stdcall OverrideView(ViewSetup* setup)
{
//overrideViewHook(clientMode, setup);
//BaseEntity* baseEntity = (BaseEntity*)entList->GetClientEntity(eng->GetLocalPlayer());

//if (!Engine->IsConnected() || !Engine->IsInGame())
//return;


//setup->fov = 120.f;


}


DWORD WINAPI Main(LPVOID hModule)
{
	//Dbg Console
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	SetConsoleTitle("Microsoft");


	pPredSeed = *(int**)(FindPattern("client.dll", "\x8B\x0D\x00\x00\x00\x00\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04", "xx????x????x????xxx") + 2);



	//Init Settings & Menu
	Menu::Init();


	vfvf0fv0f00f0();bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0();bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();


	print("[+] Hooking CreateMove\n");
	clientModeVMT = new CVMTHookManager((DWORD**)clientMode);
	bbstb0s0t0b0d00t(); vfvf0fv0f00f0(); vfvf0fv0f00f0();	bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	createMoveHook = (Hooks::oCreateMove)clientModeVMT->HookMethod((DWORD)CreateMove, 24);




	print("[+] Hooking PaintTraverse\n");
	paintTraverseVMT = new CVMTHookManager((DWORD**)Panel);
	bbstb0s0t0b0d00t();  bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	paintTraverseHook = (Hooks::oPaintTraverse)paintTraverseVMT->HookMethod((DWORD)PaintTraverse, 41);



	print("[+] Hooking FrameStageNotify\n");
	//client dll
	baseClientDLLVMT = new CVMTHookManager((DWORD**)baseClientDLL);
	bbstb0s0t0b0d00t(); vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); 	bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	frameStageNotifyHook = (Hooks::oFrameStageNotify)baseClientDLLVMT->HookMethod((DWORD)FrameStageNotify, 36);




	/*
	print("[+] Hooking OverrideView\n");
	overrideViewVMT = new CVMTHookManager((DWORD**)clientMode);
	overrideViewHook = (Hooks::oOverrideView)overrideViewVMT->HookMethod((DWORD)OverrideView, 18);



	//Surface->SetFontGlyphSet(F::Watermark = Surface->Create_Font(), charenc("System"), 12, FW_BOLD, NULL, NULL, FONTFLAG_OUTLINE, 0, 0);
	//DrawString(F::Watermark, 5, 11, Color::Purple(), FONT_LEFT, charenc("Stepen <3"));
	*/


	vfvf0fv0f00f0(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); 	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t();	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();



	//Unhook
	while (!GetAsyncKeyState(VK_END)) //if i press end
		Sleep(1000);


	isUnhooking = true;
	Sleep(500);
	//UnHook((HMODULE)hModule);



	clientModeVMT->UnHook();
	paintTraverseVMT->UnHook();
	baseClientDLLVMT->UnHook();
	//overrideViewVMT->UnHook();

	delete clientModeVMT;
	delete paintTraverseVMT;
	delete baseClientDLLVMT;
	//delete overrideViewVMT;


	print("Detaching DLL...\n");
	FreeConsole();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);

	return 0;

}


void __fastcall InitThread(DWORD arg1, DWORD arg2, HMODULE hModule) {
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); iviinfldine();
	bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
	vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
	bbstb0s0t0b0d00t(); iviinfldine();


	MainThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, 0); //here init
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	DWORD arg1 = 0;
	DWORD arg2 = arg1;

	switch (dwReason)
	{


	//Attach
	case DLL_PROCESS_ATTACH:
		vfvf0fv0f00f0(); vfvf0fv0f00f0(); bbstb0s0t0b0d00t();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		bbstb0s0t0b0d00t();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		bbstb0s0t0b0d00t();
		bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
		bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t(); bbstb0s0t0b0d00t();
		vfvf0fv0f00f0(); bbstb0s0t0b0d00t(); vfvf0fv0f00f0();
		bbstb0s0t0b0d00t(); iviinfldine();


		DisableThreadLibraryCalls((HINSTANCE)hModule);


		vfvf0fv0f00f0(); vfvf0fv0f00f0(); bbstb0s0t0b0d00t();
		bbstb0s0t0b0d00t(); iviinfldine();

		if(FindWindow("Valve001", 0))
			InitThread(arg1, arg2, hModule); //init our thread

	

		break;



	//Deatch
	case DLL_PROCESS_DETACH:
		if (MainThread)
			CloseHandle(MainThread);
		break;
	}

	return TRUE;
}










