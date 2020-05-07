#pragma once

#include <Windows.h>
#include <iostream>

#include "QAngle.h"
#include "getvfunc.h"
#include "CVMTHookManager.h"
#include "Math.h"




struct model_t;


class ICollideable
{
public:
	virtual void pad0();
	virtual Vector& OBBMins();
	virtual Vector& OBBMaxs();
};



class CBaseCombatWeapon;


class BaseEntity
{
public:
	//typedef int(__thiscall* oGetTeam)(void*);
	//typedef void(__thiscall* oRenderBounds)(void*, Vector&, Vector&);
	//typedef bool(__thiscall* oAlive)(void*);
	//typedef bool(*oSetupBones)(void*, matrix3x4*, int, int, float);


	/*
	void GetRenderBounds(Vector& min, Vector& max)
	{
		void* renderable = (PVOID)(this + 0x4);
		return getvfunc<oRenderBounds>(this, 20)(renderable, min, max);
	}

	bool IsAlive()
	{
		return getvfunc<oAlive>(this, 200)(this);
	}
	*/



	Vector GetVelocity()
	{
		return *(Vector*)((DWORD)this + 0x110);
	}

	bool IsAlive()
	{
		return (bool)(*(int*)((DWORD)this + 0x25B) == 0);
	}


	char* GetClass() {
		DWORD pNext = *(DWORD*)(this + 8);
		pNext = *(DWORD*)(pNext + 8);
		pNext = *(DWORD*)(pNext + 1);
		return *(char**)(pNext + 8);
	}

	bool IsDormant()
	{
		return *(bool*)((DWORD)this + 0xE9);
	}

	model_t* GetModel()
	{
		return *(model_t**)((DWORD)this + 0x6C);
	}

	unsigned int GetTickBase()
	{
		return *(unsigned int*)((uintptr_t)this + 0x3404);

	}

	int GetFlags()
	{
		return *(int*)((DWORD)this + 0x100);
	}

	int GetShotsFired()
	{
		return *(int*)((DWORD)this + 0xA2A0);
	}

	bool IsShooting() {
		if (this->GetShotsFired() >= 1)
			return true;

		return false;
	}

	Vector GetOrigin() //Vector GetOrigin()
	{
		return *(Vector*)((DWORD)this + 0x134);
	}

	QAngle GetPunchAngles()
	{
		return *(QAngle*)((DWORD)this + 0x301C);

	}

	QAngle GetViewPunchAngles()
	{
		return *(QAngle*)((DWORD)this + 0x3010);

	}

	Vector GetEyePos() {
		return *(Vector*)((DWORD)this + 0x104) + GetOrigin();
	}

	QAngle& GetAbsAngles()
	{
		//return *(QAngle*)((DWORD)this + 0x4D0C);
	}


	int InCross()
	{
		return *(int*)((DWORD)this + 0xB294);
	}

	int GetTeam()
	{
		return *(int*)((DWORD)this + (DWORD)0xF0);
	}


	int GetHealth()
	{
		return *(int*)((DWORD)this + (DWORD)0xFC);
	}

	bool IsSpotted()
	{
		return *(bool*)((DWORD)this + (DWORD)0x939);
	}


	float* GetLowerBodyYaw() {
		//return (float*)((DWORD)this + 0xE6996CCF);
		return (float*)((DWORD)this + 0x39F8);
	}


	Vector GetBonePosition(int bone)
	{
		matrix3x4 matrix[128];

		if (this->SetupBones(matrix, 128, 0x100, 0))
			return Vector(matrix[bone][0][3], matrix[bone][1][3], matrix[bone][2][3]);

		return Vector(0, 0, 0);
	}

	bool SetupBones(matrix3x4* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
	{
		__asm
		{
			mov edi, this
			lea ecx, dword ptr ds : [edi + 0x4]
			mov edx, dword ptr ds : [ecx]
			push currentTime
			push boneMask
			push nMaxBones
			push pBoneToWorldOut
			call dword ptr ds : [edx + 0x34]
		}
	}

	ICollideable* GetCollideable()
	{
		return (ICollideable*)((DWORD)this + 0x318);
	}

	bool IsPlayer() {
		typedef bool(__thiscall* oIsPlayer)(void*);
		return getvfunc<oIsPlayer>(this, 152)(this);
	}

	bool IsValid() {
		if (!this)
			return false;

		if (!this->IsAlive())
			return false;

		if (this->IsDormant())
			return false;

		if (this->GetTeam() != 2 && this->GetTeam() != 3)
			return false;

		if (!this->IsPlayer())
			return false;

		return true;
	}



};

