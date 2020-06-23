#ifndef CONVAR_H
#define CONVAR_H

#include "BaseEntity.h"
#include "getvfunc.h"
#include "Color.h"

namespace Interfaces {


	class ConVar
	{
	public:
		// got this from TGF aswell, 
		// ignore the typedef that doesn't really follow my other styles
		// i just chose to change the names to original when I made this class
		void SetValue(const char* value)
		{
			typedef void(__thiscall* original)(void*, const char*);
			return getvfunc<original>(this, 14)(this, value);
		}

		void SetValue(float value)
		{
			typedef void(__thiscall* original)(void*, float);
			return getvfunc<original>(this, 15)(this, value);
		}

		void SetValue(int value)
		{
			typedef void(__thiscall* original)(void*, int);
			return getvfunc<original>(this, 16)(this, value);
		}

		void SetValue(Color value)
		{
			typedef void(__thiscall* original)(void*, Color);
			return getvfunc<original>(this, 17)(this, value);
		}

		void InternalSetString(const char* str)
		{

		}

		char* GetName()
		{
			typedef char*(__thiscall* original)(void*);
			return getvfunc<original>(this, 5)(this);
		}

		char* GetDefault()
		{
			return pszDefaultValue;
		}

		char pad_0x0000[0x4]; //0x0000
		ConVar* pNext; //0x0004 
		__int32 bRegistered; //0x0008 
		char* pszName; //0x000C 
		char* pszHelpString; //0x0010 
		__int32 nFlags; //0x0014 
		char pad_0x0018[0x4]; //0x0018
		ConVar* pParent; //0x001C 
		char* pszDefaultValue; //0x0020 
		char* strString; //0x0024 
		__int32 StringLength; //0x0028 
		float fValue; //0x002C 
		__int32 nValue; //0x0030 
		__int32 bHasMin; //0x0034 
		float fMinVal; //0x0038 
		__int32 bHasMax; //0x003C 
		float fMaxVal; //0x0040 
		void* fnChangeCallback; //0x0044 
	};//Size=0x0048


}
#endif
