#pragma once

/* credits @unknowncheats */
template<typename Function>Function getvfunc(void*_VMT, int Index)
{
	void***_TVMT = (void***)_VMT;
	void**VMT = *_TVMT;
	void*_Address = VMT[Index];
	return(Function)(_Address);
}


template<typename T>
inline T ReadPtr(void* base, unsigned long offset)
{
	return *(T*)((char*)base + offset);
}



template <typename T>
T CallVFunc(void *vTable, int iIndex) {
	return (*(T**)vTable)[iIndex];
}


inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}

inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}