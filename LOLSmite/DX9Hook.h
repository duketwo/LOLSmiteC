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
	DWORD *vTable;
	CMemory m_cMemory;
	DWORD WINAPI SetupEndsceneHook();
	static DWORD WINAPI ThreadProcForObject(LPVOID param);
	static HRESULT WINAPI HkEndScene(LPDIRECT3DDEVICE9 pDevice);
};

