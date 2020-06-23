#include "SDK.h"

vec_t BitsToFloat(uint32 i)
{
	union Convertor_t
	{
		vec_t f;
		unsigned long ul;
	}tmp;
	tmp.ul = i;
	return tmp.f;
}

uint32 const FloatBits(const vec_t &f)
{
	union Convertor_t
	{
		vec_t f;
		uint32 ul;
	}tmp;
	tmp.f = f;
	return tmp.ul;
}

inline bool IsFinite(const vec_t &f)
{
#if _X360
	return f == f && fabs(f) <= FLT_MAX;
#else
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
#endif
}
