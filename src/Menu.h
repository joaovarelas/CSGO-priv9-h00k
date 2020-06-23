#pragma once


namespace Settings {
	extern float AutoStop;

	extern float AntiAim;
	extern float AntiAimX; //0-7
	extern float AntiAimY; //0-10

	extern float Aimbot;
	extern float FOV;
	extern float AimBone;
	extern float AimTeam;
	extern float AimSilent;
	extern float AimKey;
	extern float AutoShoot;
	extern float AutoPistol;
	extern float ShootDelay;

	extern float NoRecoil;
	extern float NoVisRecoil;
	extern float Triggerbot;
	extern float BunnyHop;
	extern float AirStuck;
	extern float AutoRevolver;
	extern float Prediction;

	extern float EspBox;
	extern float EspName;
	extern float EspHealth;
	extern float Radar;

	

}



namespace Menu {
	void DrawString(HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ...);
	void Init();
	void Draw();

}

extern HFont hfont;


