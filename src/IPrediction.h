#pragma once

#include <Windows.h>
#include "BaseEntity.h"
#include "InputSystem.h"

struct MoveData { byte Data[256]; };
namespace Interfaces {


	class IGameMovement
	{
	public:
		virtual			~IGameMovement(void) {}

		virtual void	ProcessMovement(BaseEntity *pPlayer, MoveData *pMove) = 0;
		virtual void	Reset(void) = 0;
		virtual void	StartTrackPredictionErrors(BaseEntity *pPlayer) = 0;
		virtual void	FinishTrackPredictionErrors(BaseEntity *pPlayer) = 0;
		virtual void	DiffPrint(char const *fmt, ...) = 0;

		virtual Vector const&	GetPlayerMins(bool ducked) const = 0;
		virtual Vector const&	GetPlayerMaxs(bool ducked) const = 0;
		virtual Vector const& GetPlayerViewOffset(bool ducked) const = 0;

		virtual bool			IsMovingPlayerStuck(void) const = 0;
		virtual BaseEntity*	GetMovingPlayer(void) const = 0;
		virtual void			UnblockPusher(BaseEntity* pPlayer, BaseEntity *pPusher) = 0;

		virtual void SetupMovementBounds(MoveData *pMove) = 0;
	};

	class IMoveHelper
	{
	public:
		void SetHost(BaseEntity* pPlayer)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, BaseEntity* pPlayer);
			getvfunc< OriginalFn >(this, 1)(this, pPlayer);
		}
	};

	class IPrediction {
	public:
		virtual void UnknownVirtual0() = 0;
		virtual void UnknownVirtual1() = 0;
		virtual void UnknownVirtual2() = 0;
		virtual void UnknownVirtual3() = 0;
		virtual void UnknownVirtual4() = 0;
		virtual void UnknownVirtual5() = 0;
		virtual void UnknownVirtual6() = 0;
		virtual void UnknownVirtual7() = 0;
		virtual void UnknownVirtual8() = 0;
		virtual void UnknownVirtual9() = 0;
		virtual void UnknownVirtual10() = 0;
		virtual void UnknownVirtual11() = 0;
		virtual void UnknownVirtual12() = 0;
		virtual void UnknownVirtual13() = 0;
		virtual void UnknownVirtual14() = 0;
		virtual void UnknownVirtual15() = 0;
		virtual void UnknownVirtual16() = 0;
		virtual void UnknownVirtual17() = 0;
		virtual void UnknownVirtual18() = 0;
		virtual void UnknownVirtual19() = 0;
		virtual void SetupMove(BaseEntity* player, CUserCmd* ucmd, void* pHelper, MoveData* move) = 0; //20
		virtual void FinishMove(BaseEntity* player, CUserCmd* ucmd, MoveData* move) = 0;
	};


}


extern int* pPredSeed;