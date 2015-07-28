
#include "stdafx.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <iomanip>
#include "Memory.h"
#include "Util.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "DX9Hook.h"

typedef HRESULT(WINAPI* EndScene_t)(LPDIRECT3DDEVICE9 pDevice);
static HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
static EndScene_t pEndScene;
LPDIRECT3DDEVICE9 CDX9Hook::device;
CCore CDX9Hook::m_core;

CDX9Hook::CDX9Hook()
{

}

CDX9Hook::~CDX9Hook()
{
	m_cMemory.~CMemory();
	m_core.~CCore();
}


static VOID WriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, LPCWSTR text)
{
	LPD3DXFONT pFont;
	RECT rect;
	SetRect(&rect, x, y, x, y);
	D3DXCreateFont(pDevice, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);
	pFont->DrawText(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
}

bool CDX9Hook::Mask(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD CDX9Hook::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (this->Mask((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);
	return 0;
}

void DrawRect(LPDIRECT3DDEVICE9 Device_t, int X, int Y, int L, int H, D3DCOLOR color)
{
	D3DRECT rect = { X, Y, X + L, Y + H };
	Device_t->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

HRESULT CDX9Hook::HkEndScene(LPDIRECT3DDEVICE9 pDevice) {

	m_core.EndSceneLoop();

	if (device == NULL) {
		device = pDevice;
	}

	DrawRect(pDevice, 100, 100, 100, 100, D3DCOLOR_ARGB(255, 255, 0, 255));
	return pEndScene(pDevice);
}

DWORD WINAPI CDX9Hook::SetupEndsceneHook()
{
	CUtil::instance()->addLog("Thread created!");

	HMODULE hModule = NULL;
	while (!hModule)
	{
		hModule = GetModuleHandleA("d3d9.dll"); // get dll handle
		Sleep(100);
	}
	CUtil::instance()->addLog("D3D9.dll found!");
	DWORD tempadd = FindPattern((DWORD)hModule, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	memcpy(&vTable, (void*)(tempadd + 2), 4);
	DWORD dwEndScene = vTable[42];
	pEndScene = m_cMemory.Patch<EndScene_t>(CMemory::Inline, (DWORD)dwEndScene, (DWORD)HkEndScene);

	return 0;
}

void CDX9Hook::InitHook(bool fAllocConsole) {
	if (fAllocConsole) {
		this->FAllocConsole();
	}
	LPSECURITY_ATTRIBUTES security_attributes = 0;
	SIZE_T stack_size = 0;
	LPTHREAD_START_ROUTINE start_routine = &CDX9Hook::ThreadProcForObject;
	LPVOID param = this;
	DWORD creation_flags = 0;
	LPDWORD thread_id = 0;
	CreateThread(security_attributes, stack_size, start_routine, param,
		creation_flags, thread_id);
}

void CDX9Hook::FAllocConsole() {

	AllocConsole();
	FILE* f1;
	FILE* f2;
	FILE* f3;
	freopen_s(&f1, "CONOUT$", "wb", stdout);
	freopen_s(&f2, "CONOUT$", "wb", stderr);
	freopen_s(&f3, "CONIN$", "rb", stdin);
}


DWORD WINAPI CDX9Hook::ThreadProcForObject(LPVOID param) {
	CDX9Hook* instance = reinterpret_cast<CDX9Hook*>(param);
	if (!instance) return 1;
	return instance->SetupEndsceneHook();
}


