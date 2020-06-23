#pragma once
#include <windows.h>


typedef void* (*oInterface)(char*, int);

namespace Interface
{
	class InterfaceTools
	{
	public:
		void* GetInterface(char* moudleName, char* interfaceName);

	};

}

