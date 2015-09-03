#pragma once
class CCore
{
public:
	CCore();
	~CCore();
	void EndSceneLoop();
	bool firstFrame;
	ULONGLONG m_dwLastCheck;
	HWND m_hWnd;
};

