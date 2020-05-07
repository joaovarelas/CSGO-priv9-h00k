#pragma once
#pragma warning( disable : 4244)
#pragma warning( disable : 4996)

#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <d3d9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <vector>
#include <Psapi.h>

//Sauce Engine SDK
#include "BaseEntity.h"
#include "Interface.h"
#include "Math.h"
#include "Hooks.h"
#include "CVMTHookManager.h"
#include "Engine.h"
#include "ClientMode.h"
#include "BaseClientDLL.h"
#include "InputSystem.h"
#include "ClientEntityList.h"
#include "getvfunc.h"
#include "Hooks.h"
#include "QAngle.h"
#include "UserCmd.h"
//#include "Chat.h"
#include "ClientModeShared.h"
#include "ConVar.h"
#include "CVar.h"
#include "ViewSetup.h"
#include "Surface.h"
#include "Panel.h"
#include "CBaseTrace.h"
#include "CGameTrace.h"
#include "ITraceFilter.h"
#include "CTraceFilter.h"
#include "IEngineTrace.h"
#include "IPrediction.h"
#include "CGlobalVars.h"


#include "xor.h"
#include "Menu.h"
#include "Hacks.h"



//debug
#define box(x) MessageBox(0, x,x,0)
#define print(x, ...) printf(x);std::cout.clear()

			


