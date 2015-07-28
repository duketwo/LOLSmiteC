#include "stdafx.h"
//#include "DxHook.h"
//#include <windows.h>
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <stdio.h>
//#include <sstream>
//#include <string>
//#include <iomanip>
//
//#pragma comment(lib, "d3d9.lib")
//#pragma comment(lib, "d3dx9.lib")
//
//
//DWORD *vTable;
//HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
//typedef HRESULT(WINAPI* EndScene_t)(LPDIRECT3DDEVICE9 pDevice);
//EndScene_t pEndScene;
//CMemory m_cMemory;
//
//
//DxHook::DxHook()
//{
//}
//
//
//
//VOID DxHook::WriteText(LPDIRECT3DDEVICE9 pDevice, INT x, INT y, DWORD color, LPCWSTR text)
//{
//
//	LPD3DXFONT pFont;
//	RECT rect;
//	SetRect(&rect, x, y, x, y);
//	D3DXCreateFont(pDevice, 14, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &pFont);
//	pFont->DrawText(NULL, text, -1, &rect, DT_NOCLIP | DT_LEFT, color);
//}
//
//
//bool DxHook::Mask(const BYTE* pData, const BYTE* bMask, const char* szMask)
//{
//	for (; *szMask; ++szMask, ++pData, ++bMask)
//		if (*szMask == 'x' && *pData != *bMask)
//			return false;
//	return (*szMask) == NULL;
//}
//
//DWORD DxHook::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
//{
//	for (DWORD i = 0; i<dwLen; i++)
//		if (Mask((BYTE*)(dwAddress + i), bMask, szMask))
//			return (DWORD)(dwAddress + i);
//	return 0;
//}
//
//
//void DxHook::DrawRect(LPDIRECT3DDEVICE9 Device_t, int X, int Y, int L, int H, D3DCOLOR color)
//{
//
//	D3DRECT rect = { X, Y, X + L, Y + H };
//	Device_t->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
//}
//
//HRESULT WINAPI DxHook::hkEndScene(LPDIRECT3DDEVICE9 pDevice) 
//{
//	//WriteText(pDevice, 400, 400, D3DCOLOR_ARGB(255, 255, 0, 255), L"yolo");
//	DrawRect(pDevice, 100, 100, 100, 100, D3DCOLOR_ARGB(255, 255, 0, 255));
//	return pEndScene(pDevice);
//}
//DWORD WINAPI DxHook::InitHook()
//{
//	add_log("Thread erstellt!");
//	HMODULE hModule = NULL;
//	while (!hModule)
//	{
//		hModule = GetModuleHandleA("d3d9.dll"); // Handle zur DLL holen
//		Sleep(100); // 100ms warten
//	}
//	add_log("d3d9.dll gefunden!");
//
//	DWORD tempadd = FindPattern((DWORD)hModule, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
//	memcpy(&vTable, (void*)(tempadd + 2), 4);
//	DWORD dwEndScene = vTable[42];
//
//	std::ostringstream stream;
//	stream.flags(std::ios::hex);
//	stream << dwEndScene;
//	std::string args = stream.str();
//	args = "hex Vtable: " + args;
//
//	add_log((char*)DWORDToHexString("", dwEndScene).c_str());
//	add_log((char*)args.c_str());
//
//	pEndScene = m_cMemory.Patch<EndScene_t>(CMemory::Inline, dwEndScene, (DWORD)hkEndScene);
//	return 0;
//
//}
//
//std::string DxHook::DWORDToHexString(std::string pr, DWORD dex) 
//{
//	std::ostringstream stream;
//	stream.flags(std::ios::hex);
//	stream << dex;
//	std::string args = stream.str();
//	args = pr + args;
//	return args;
//}
//
//void DxHook::add_log(char* string)
//{
//	HANDLE filehandle;
//	DWORD dwReadBytes;
//	char buffer[2048];
//	filehandle = CreateFile(L"Log.txt", GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
//	SetFilePointer(filehandle, 0, 0, FILE_END);
//	sprintf_s(buffer, 1024, "Added Log: %s\r\n", string);
//	WriteFile(filehandle, buffer, strlen(buffer), &dwReadBytes, 0);
//	CloseHandle(filehandle);
//}
//
//
//
//DxHook::~DxHook()
//{
//}
