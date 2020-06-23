#pragma once

#include "Math.h"
#include "CGameTrace.h"


#define	CONTENTS_SOLID			0x1
#define	CONTENTS_WINDOW			0x2
#define CONTENTS_MOVEABLE		0x4000
#define	CONTENTS_MONSTER		0x2000000
#define	CONTENTS_DEBRIS			0x4000000
#define CONTENTS_HITBOX			0x40000000

#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	const   matrix3x4* m_pWorldAxisTransform;

	bool    m_IsRay;
	bool    m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(0) { }

	void Init(Vector& start, Vector& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents.Set();
		m_pWorldAxisTransform = 0;
		m_IsRay = true;

		m_StartOffset.Set();
		m_Start = start;
	}

	void Init(Vector& start, Vector& end, Vector& mins, Vector& maxs)
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = 0;
		m_IsSwept = (m_Delta.Length() != 0);

		m_Extents = maxs - mins;
		m_Extents = m_Extents* 0.5f;
		m_IsRay = (m_Extents.Length() < 1e-6);

		m_StartOffset = mins + maxs;
		m_StartOffset = m_StartOffset*0.5f;
		m_Start = start - m_StartOffset;
		m_StartOffset = m_StartOffset * -1.0f;
	}
};




namespace Interfaces{
	class IEngineTrace
	{
	public:
		void TraceRay(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)
		{
			typedef void(__thiscall* TraceRayFn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
			return getvfunc<TraceRayFn>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
		}
	};
}
