 #pragma once

#include "ViewSetup.h"
#include "InputSystem.h"
#include "ClientFrameStage.h"

/*
	This namespace is ONLY for hooks that are actually major (createmove, painttraverse, etc.)
	Sorry if this is confusing
*/

namespace Hooks
{

	typedef void(__thiscall* oCreateMove)(void*, float, CUserCmd*);
	typedef void(__thiscall* oOverrideView)(void*, ViewSetup* setup);
	typedef void(__thiscall* oPaintTraverse)(void*, unsigned int, bool, bool);
	typedef void(__thiscall* oFrameStageNotify)(void*, ClientFrameStage_t stage);
}

