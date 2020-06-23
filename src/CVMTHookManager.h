#pragma once

#include <Windows.h>

// credits @uc
class CVMTHookManager
{
private:
	PDWORD*	m_ppdwClassBase;
	PDWORD	m_pdwNewVMT, m_pdwOldVMT;
	DWORD	m_dwVMTSize;

public:
	CVMTHookManager(void);

	CVMTHookManager(PDWORD* ppdwClassBase);

	~CVMTHookManager(void);

	bool Initialize(PDWORD* ppdwClassBase);

	bool Initialize(PDWORD** pppdwClassBase);

	void UnHook(void);

	void ReHook(void);

	int GetFuncCount(void);

	DWORD GetMethodAddress(int Index);

	PDWORD GetOldVMT(void);

	DWORD HookMethod(DWORD dwNewFunc, unsigned int iIndex);

	template< class T > T GetMethod(unsigned int nIndex) const;

	inline void* GetFunction(void* Instance, int Index);


private:
	DWORD GetVMTCount(PDWORD pdwVMT);
};
