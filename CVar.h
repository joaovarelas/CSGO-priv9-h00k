#pragma once

#include "ConVar.h"
#include "getvfunc.h"

namespace Interfaces{
	class CVar
	{
	public:
		typedef ConVar*(__thiscall* oFindVar)(void*, const char*);

		ConVar* FindVar(const char* name)
		{
			return getvfunc<oFindVar>(this, 14)(this, name);
		}
	};
}

