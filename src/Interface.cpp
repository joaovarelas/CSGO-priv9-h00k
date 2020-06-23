#include "SDK.h"


void* Interface::InterfaceTools::GetInterface(char* moudleName, char* interfaceName)
{
	oInterface original = (oInterface)GetProcAddress(GetModuleHandleA(moudleName), "CreateInterface");

	return (void*)original(interfaceName, 0);
}