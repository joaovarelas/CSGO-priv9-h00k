#pragma once

#include "getvfunc.h"

namespace Interfaces{
	class Panel
	{
	public:
		const char* GetName(int panelID)
		{
			typedef const char* (__thiscall* oPanel) (void*, int);

			return getvfunc<oPanel>(this, 36)(this, panelID);
		}
	};
};
