#pragma once
class CCore
{
public:
	CCore();
	~CCore();
	void EndSceneLoop();
	bool firstFrame;
	DWORD m_dwLastCheck;
	HWND m_hWnd;
};

