#include "SDK.h"

//junk code 4 vacation
struct st0s0t00s00s0t0s0t00s0t0s0 {
	bool vac = (bool)0;
};
class cl0lccclcl000000clclc000lc0lc {
public:
	float x;
	float y;
	float z;
	bool vac;
};




extern Interfaces::Surface* Surface;



void Menu::DrawString(HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int width, height;
	Surface->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextColor(color.R(), color.G(), color.B(), color.A());
	Surface->DrawSetTextPos(x, y - height / 2);
	Surface->DrawPrintText(wbuf, wcslen(wbuf), FONT_DRAW_DEFAULT);
}

void DrawRect(int x, int y, int w, int h, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawFilledRect(x, y, x + w, y + h);
}

void DrawOutRect(int x, int y, int w, int h, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawOutlinedRect(x, y, x + w, y + h);
}



// CS:S MENU AHAH
// github.com/joaovarelas/h00k-game-hack/needed.cpp



void Menu::Init() {
	Surface->SetFontGlyphSet(hfont = Surface->Create_Font(), XorStr("Verdana"), 15, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE);

	Settings::Aimbot = 0;
	Settings::Triggerbot = 1;
	Settings::FOV = 4.f;
	Settings::AimBone = 8;
	Settings::AimTeam = 0;
	Settings::AimSilent = 0;
	Settings::AimKey = 1;
	Settings::AutoShoot = 0;
	Settings::AutoPistol = 0;
	Settings::ShootDelay = 0;

	Settings::EspBox = 2;
	Settings::EspName = 1;
	Settings::EspHealth = 1;
	Settings::Radar = 1;

	Settings::NoRecoil = 0;
	Settings::NoVisRecoil = 0;

	Settings::BunnyHop = 1;
	Settings::Prediction = 1;
	Settings::AirStuck = 0;
	Settings::AutoStop = 0;
	Settings::AutoRevolver = 0;



}

float tab1, tab2, tab3, tab4;

bool bKeyPressed[256];
bool IsKeyPressed(int iKey) {
	if (GetAsyncKeyState(iKey)) {
		if (!bKeyPressed[iKey]) {
			bKeyPressed[iKey] = true;
			return true;
		}
	}
	else
		bKeyPressed[iKey] = false;

	return false;
}


struct menu_s
{
	char *title;
	float* value;
	float min;
	float max;
	float step;
	bool isTab;
};

menu_s menu[150];

int AddMenuEntry(int n, char* title, float* value, float min, float max, float step, bool btab = false)
{
	menu[n].title = title;
	menu[n].value = value;
	menu[n].min = min;
	menu[n].max = max;
	menu[n].step = step;
	menu[n].isTab = btab;
	return (n + 1);
}

int menuIndex = 0;
int menuItems = 0;

void Menu::Draw() {



	int i = 0;
	
	i = AddMenuEntry(i, "[+] Aimbot", &tab1, 0, 1, 1, true);
	if (tab1 == 1)
	{
		i = AddMenuEntry(i, "\tEnabled", &Settings::Aimbot, 0, 1, 1);
		i = AddMenuEntry(i, "\tTriggerbot", &Settings::Triggerbot, 0, 1, 1);
		i = AddMenuEntry(i, "\tFOV", &Settings::FOV, 0.f, 180.f, 2.f);
		i = AddMenuEntry(i, "\tAimBone", &Settings::AimBone, 1, 8, 1);
		i = AddMenuEntry(i, "\tTeammates", &Settings::AimTeam, 0, 1, 1);
		i = AddMenuEntry(i, "\tSilent", &Settings::AimSilent, 0, 1, 1);
		i = AddMenuEntry(i, "\tAimKey", &Settings::AimKey, 0, 1, 1);
		i = AddMenuEntry(i, "\tAutoShoot", &Settings::AutoShoot, 0, 1, 1); 
		i = AddMenuEntry(i, "\tShootDelay", &Settings::ShootDelay, 0, 20, 1);
		//i = AddMenuEntry(i, "\tAutoPistol", &Settings::AutoPistol, 0, 1, 1);

	}

	i = AddMenuEntry(i, "[+] Visuals", &tab2, 0, 1, 1, true);

	if (tab2 == 1)
	{
		i = AddMenuEntry(i, "\tESP Box", &Settings::EspBox, 0, 2, 1);
		i = AddMenuEntry(i, "\tESP Name", &Settings::EspName, 0, 1, 1);
		i = AddMenuEntry(i, "\tESP Health", &Settings::EspHealth, 0, 1, 1);
		i = AddMenuEntry(i, "\tRadar", &Settings::Radar, 0, 1, 1);

	}



	i = AddMenuEntry(i, "[+] Removals", &tab3, 0, 1, 1, true);
	if (tab3 == 1)
	{
		i = AddMenuEntry(i, "\tNo Recoil", &Settings::NoRecoil, 0, 1, 1);
		i = AddMenuEntry(i, "\tNo Vis. Recoil", &Settings::NoVisRecoil, 0, 1, 1);

	}
	


	i = AddMenuEntry(i, "[+] Misc", &tab4, 0, 1, 1, true);
	if (tab4 == 1)
	{
		i = AddMenuEntry(i, "\tBunnyhop", &Settings::BunnyHop, 0, 1, 1);
		i = AddMenuEntry(i, "\tAirStuck", &Settings::AirStuck, 0, 1, 1);
		i = AddMenuEntry(i, "\tAutoStop", &Settings::AutoStop, 0, 1, 1);
		i = AddMenuEntry(i, "\tAutoRevolver", &Settings::AutoRevolver, 0, 1, 1);
		i = AddMenuEntry(i, "\tEnginePrediction", &Settings::Prediction, 0, 1, 1);

	}

	/*
	i = AddMenuEntry(i, "[+] AntiAim", &tab4, 0, 1, 1, true);
	if (tab4 == 1)
	{
		i = AddMenuEntry(i, "\tEnabled", &Settings::AntiAim, 0, 1, 1);
		i = AddMenuEntry(i, "\tPitch", &Settings::AntiAimX, 0, 7, 1);
		i = AddMenuEntry(i, "\tYaw", &Settings::AntiAimY, 0, 14, 1);

	}
	*/



	menuItems = i;

	int x = 420;
	int y = 30;
	int w = 150;
	int h = 16;


	//watermark
	DrawOutRect(x - 1, y  - 11, w + 2, 17, Color::Red());
	DrawRect(x, y-10 , w, 15, Color::Grey());
	DrawString(hfont, x+2, y-2, Color::White(), FONT_LEFT, "priv8 h00k");


	//settings menu
	DrawOutRect(x - 1, y + 10 - 1, w + 2, menuItems * 16 + 6, Color::Red());
	DrawRect(x, y + 10, w, menuItems * 16 + 4, Color::Grey());

	//Draw Menu Items
	for (int i = 0; i < menuItems; i++) {

		//float -> wchar -> char*
		int vIn = (int)*menu[i].value;
		wchar_t vOut[12];
		_itow_s(vIn, vOut, sizeof(vOut) / 2, 10);
		char mbstr[11];
		std::wcstombs(mbstr, vOut, 11);

		DrawString(hfont, x + 5, y + (16 * i) + 20, (i == menuIndex) ? Color::Red() : Color::White(), FONT_LEFT, menu[i].title);
		
		if(!menu[i].isTab)
			DrawString(hfont, x + 5 + 100 + 20, y + (16 * i) + 20, (i == menuIndex) ? Color::Red() : Color::White(), FONT_LEFT, mbstr);

	}



	//Settings
	if (IsKeyPressed(VK_UP)) //uparrow || mwheelup
	{
		if (menuIndex > 0) menuIndex--;
		else menuIndex = menuItems - 1;
	}

	else if (IsKeyPressed(VK_DOWN)) //downarrow || mwheeldown
	{
		if (menuIndex < menuItems - 1) menuIndex++;
		else menuIndex = 0;
	}


	else if (IsKeyPressed(VK_LEFT)) //leftarrow || leftbutton
	{
		if (menu[menuIndex].value)
		{
			menu[menuIndex].value[0] -= menu[menuIndex].step;
			if (menu[menuIndex].value[0] < menu[menuIndex].min)
				menu[menuIndex].value[0] = menu[menuIndex].max;
		}
	}

	else if (IsKeyPressed(VK_RIGHT)) //rightarrow || rightbutton
	{
		if (menu[menuIndex].value)
		{
			menu[menuIndex].value[0] += menu[menuIndex].step;
			if (menu[menuIndex].value[0] > menu[menuIndex].max)
				menu[menuIndex].value[0] = menu[menuIndex].min;
		}

	}

}