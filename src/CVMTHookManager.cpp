#include "CVMTHookManager.h"



CVMTHookManager::CVMTHookManager(void)
{
	memset(this, 0, sizeof(CVMTHookManager));
}

CVMTHookManager::CVMTHookManager(PDWORD* ppdwClassBase)
{
	Initialize(ppdwClassBase);
}

CVMTHookManager::~CVMTHookManager(void)
{
	UnHook();
}

bool CVMTHookManager::Initialize(PDWORD* ppdwClassBase)
{
	m_ppdwClassBase = ppdwClassBase;
	m_pdwOldVMT = *ppdwClassBase;
	m_dwVMTSize = GetVMTCount(*ppdwClassBase);
	m_pdwNewVMT = new DWORD[m_dwVMTSize];
	memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD) * m_dwVMTSize);
	*ppdwClassBase = m_pdwNewVMT;
	return true;
}

bool CVMTHookManager::Initialize(PDWORD** pppdwClassBase)
{
	return Initialize(*pppdwClassBase);
}

void CVMTHookManager::UnHook(void)
{
	if (m_ppdwClassBase)
	{
		*m_ppdwClassBase = m_pdwOldVMT;
	}
}

void CVMTHookManager::ReHook(void)
{
	if (m_ppdwClassBase)
	{
		*m_ppdwClassBase = m_pdwNewVMT;
	}
}

int CVMTHookManager::GetFuncCount(void)
{
	return (int)m_dwVMTSize;
}

DWORD CVMTHookManager::GetMethodAddress(int Index)
{
	if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != NULL)
	{
		return m_pdwOldVMT[Index];
	}
	return NULL;
}

PDWORD CVMTHookManager::GetOldVMT(void)
{
	return m_pdwOldVMT;
}

DWORD CVMTHookManager::HookMethod(DWORD dwNewFunc, unsigned int iIndex)
{
	if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
	{
		m_pdwNewVMT[iIndex] = dwNewFunc;
		return m_pdwOldVMT[iIndex];
	}
	return NULL;
}

template< class T > T CVMTHookManager::GetMethod(unsigned int nIndex) const
{
	return (T)m_pdwOldVMT[nIndex];
}

inline void* CVMTHookManager::GetFunction(void* Instance, int Index)
{
	DWORD VirtualFunction = (*(DWORD*)Instance) + sizeof(DWORD) * Index;
	return (void*)*((DWORD*)VirtualFunction);
}



DWORD CVMTHookManager::GetVMTCount(PDWORD pdwVMT)
{
	DWORD dwIndex = 0;

	for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
	{
		if (IsBadCodePtr((FARPROC)pdwVMT[dwIndex]))
		{
			break;
		}
	}
	return dwIndex;
}