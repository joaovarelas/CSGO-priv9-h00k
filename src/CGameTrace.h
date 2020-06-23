#pragma once

#include "CBaseTrace.h"
#include "BaseEntity.h"

struct csurface_t
{
	const char		*name;
	short			surfaceProps;
	unsigned short	flags;
};


class CGameTrace : public CBaseTrace
{
public:
	bool DidHitWorld() const;

	bool DidHitNonWorldEntity() const;

	int GetEntityIndex() const;

	bool DidHit() const
	{
		return fraction < 1 || allsolid || startsolid;
	}

public:
	float			fractionleftsolid;
	csurface_t		surface;

	int				hitgroup;

	short			physicsbone;
	unsigned short	worldSurfaceIndex;

	BaseEntity*	m_pEnt;
	int				hitbox;

	CGameTrace() {}
	CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;



enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};