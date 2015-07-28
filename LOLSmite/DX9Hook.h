
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Memory.h"
#include "string"
#include "Core.h"
#pragma once
class CDX9Hook
{
public:
	CDX9Hook();
	~CDX9Hook();
	void InitHook(bool fAllocConsole);
	void FAllocConsole();
	static LPDIRECT3DDEVICE9 device;
	
private:
	static CCore m_core;
	bool Mask(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask);
	DWORD *vTable;
	CMemory m_cMemory;
	DWORD WINAPI SetupEndsceneHook();
	static DWORD WINAPI ThreadProcForObject(LPVOID param);
	static HRESULT WINAPI HkEndScene(LPDIRECT3DDEVICE9 pDevice);
};

