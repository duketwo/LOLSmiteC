#include "stdafx.h"
#include "Core.h"
#include "Util.h"


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

	DWORD dwCurrentTickCount = GetTickCount();

	if (!firstFrame) {
		CUtil::instance()->addLog("CCore::EndSceneLoop() first frame.");
		firstFrame = true;
	}
	if (dwCurrentTickCount - m_dwLastCheck >= 100 && GetForegroundWindow() == this->m_hWnd)
	{
		if (GetAsyncKeyState(VK_F10)) {
			CUtil::instance()->addLog("F10 pressed!");
		}
		m_dwLastCheck = dwCurrentTickCount;
	}
}
