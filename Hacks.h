#pragma once
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "UserCmd.h"
#include "BaseEntity.h"
#include "Color.h"





namespace Hacks {
	void __fastcall Aimbot(CUserCmd* cmd, BaseEntity* LocalPlayer, bool& bSendPacket);
	void Triggerbot(CUserCmd* cmd, BaseEntity* LocalPlayer);
	void Bhop(CUserCmd* cmd, BaseEntity* LocalPlayer);
	void Radar(BaseEntity* pEntity);
	void NoRecoil(CUserCmd* cmd, BaseEntity* LocalPlayer);
	
	void __fastcall ESP();
	bool IsVisible(BaseEntity* target, int bone);

	void Airstuck(CUserCmd* cmd);
	void Autostop(CUserCmd* cmd);
	void ChangeName(const char* name);

	void CorrectMovement(QAngle vOldAngles, CUserCmd* cmd, float fOldForward, float fOldSidemove);

	namespace Prediction {
		void Start(CUserCmd* cmd);
		void End();
	}

}


