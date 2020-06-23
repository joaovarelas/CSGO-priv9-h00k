#pragma once




class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void *pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

#pragma once
