#pragma once

class CUtil
{
public:
	static CUtil* Instance();
	void AddLog(char* string);
	std::string GetCurrentPath();
	const std::string GetCurrentDateTime();
	unsigned int GetLOLBaseAddress();
	_MODULEINFO GetModuleInfo(HMODULE hModule);
	bool Mask(const BYTE * pData, const BYTE * bMask, const char * szMask);
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE * bMask, char * szMask);
	std::string currentPath;
	inline LPCSTR GetLOLExeName(void) { return "League of Legends.exe"; }

protected:
	CUtil();
private:
	unsigned int lolBaseAddress;
	static CUtil *inst;
	~CUtil();
};


