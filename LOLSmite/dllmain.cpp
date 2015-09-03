// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"



CDX9Hook* dx9h = new CDX9Hook();

int WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:

		dx9h->InitHook(true);

		break;
	case DLL_PROCESS_DETACH:
		dx9h->~CDX9Hook();
		delete dx9h;
		break;
	}
	
	return true;
}