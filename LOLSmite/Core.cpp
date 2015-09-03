#include "stdafx.h"
#include "ObjectManager.h"


CCore::CCore()
{
	this->m_dwLastCheck = 0;
	this->m_hWnd = FindWindow(NULL, L"League of Legends (TM) Client");
}

CCore::~CCore()
{
}


void CCore::EndSceneLoop()
{

	ULONGLONG  dwCurrentTickCount = GetTickCount64();

	if (!firstFrame) {
		CUtil::Instance()->AddLog("CCore::EndSceneLoop() first frame.");
		firstFrame = true;
	}

	CObjectManager* objManager = (CObjectManager*)(CUtil::Instance()->GetLOLBaseAddress() + COffset::ObjectManager());


	if (dwCurrentTickCount - m_dwLastCheck >= 1000 && GetForegroundWindow() == this->m_hWnd)
	{

		CUtil::Instance()->AddLog("F10 pressed!");

		CUtil::Instance()->AddLog((char*)(std::to_string(objManager->GetMaxObjects()).c_str()));


		for (int i = 0; i < objManager->GetEnd(); i++)
		{
			CUnit* unit = objManager->GetFirst()[i];

			if (unit == NULL) {
				continue;
			}

			//printf_s("%s\n", unit->GetName().getString());

		}

		if (GetAsyncKeyState(VK_F10)) {
			//std::string s = COffset::LocalPlayerMask();
			//s.replace(s.begin(), s.end(), ' ', '\x0'); // replace all 'x' to 'y'
			//printf_s("%s\n",s);
			//std::cout << s << std::endl;

			HMODULE hModule = NULL;
			while (!hModule)
			{
				hModule = GetModuleHandleA(CUtil::Instance()->GetLOLExeName()); // get dll handle
				Sleep(100);
			}

			DWORD objManager = CUtil::Instance()->FindPattern((DWORD)hModule, CUtil::Instance()->GetModuleInfo(hModule).SizeOfImage, COffset::GetObjectManagerMask(), "xxxxxxxxxxxx");
			objManager = (*((DWORD*)(objManager + 0x18))) - (DWORD)CUtil::Instance()->GetLOLBaseAddress();
			std::cout.flags(std::ios::hex);
			std::cout << objManager << std::endl;

		}

		m_dwLastCheck = dwCurrentTickCount;
	}
}
