// LOLSmiteLoader.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include <Windows.h>


int main()
{
	
	DWORD dwPid;
	HANDLE hHandle;
	void* lpRemoteString;
	HWND hWnd = FindWindow(NULL, L"League of Legends (TM) Client");

	wchar_t szPath[MAX_PATH];

	if (hWnd == NULL)
	{
		MessageBox(NULL, L"Couldn't find window!", NULL, MB_OK);
		return 1;
	}

	GetWindowThreadProcessId(hWnd, &dwPid);
	hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	lpRemoteString = VirtualAllocEx(hHandle, NULL, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	GetCurrentDirectory(sizeof(szPath), szPath);
	wcscat_s(szPath, L"\\LOLSmite.dll");

	WriteProcessMemory(hHandle, lpRemoteString, (void*)szPath, sizeof(szPath) * 2, NULL);
	MessageBox(NULL, szPath, L"Press OK to inject", MB_OK);
	HANDLE hThread = CreateRemoteThread(hHandle, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, lpRemoteString, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	DWORD dwModule;
	GetExitCodeThread(hThread, &dwModule);
	CloseHandle(hThread);
	VirtualFreeEx(hHandle, lpRemoteString, 0, MEM_FREE);
	MessageBox(NULL, szPath, L"Press OK to unload!", MB_OK);
	hThread = CreateRemoteThread(hHandle, NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, (void*)dwModule, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hHandle);

	return 0;
}

