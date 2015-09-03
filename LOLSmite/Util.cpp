#include "stdafx.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


CUtil* CUtil::inst = 0;

CUtil::CUtil()
{
	currentPath = std::string();
	lolBaseAddress = 0;
}

CUtil::~CUtil()
{
	delete CUtil::inst;
}

void CUtil::AddLog(char* string)
{
	USES_CONVERSION;
	HANDLE filehandle;
	DWORD dwReadBytes;
	char buffer[2048];
	filehandle = CreateFile(CA2W((GetCurrentPath() + "\Log.txt").c_str()), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	SetFilePointer(filehandle, 0, 0, FILE_END);
	sprintf_s(buffer, 1024, "(%s): %s\r\n", GetCurrentDateTime().c_str(), string);
	printf_s("(%s): %s\r\n", GetCurrentDateTime().c_str(), string);
	WriteFile(filehandle, buffer, strlen(buffer), &dwReadBytes, 0);
	CloseHandle(filehandle);
}

std::string CUtil::GetCurrentPath()
{
	if (currentPath.length() == 0) {
		USES_CONVERSION;
		LPTSTR  lpCurrentPath = new TCHAR[_MAX_PATH];
		GetModuleFileName((HINSTANCE)&__ImageBase, lpCurrentPath, _MAX_PATH);
		std::string currPath = W2A(lpCurrentPath);
		currPath.replace(currPath.end() - 12, currPath.end(), "\0");
		currentPath = currPath;
	}
	return currentPath;
}


const std::string CUtil::GetCurrentDateTime() 
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return boost::posix_time::to_simple_string(now);
}


 unsigned int CUtil::GetLOLBaseAddress() {
	 if (this->lolBaseAddress == 0) {
		 this->lolBaseAddress = (unsigned)GetModuleHandleA("League of Legends.exe");
	 }
	 return this->lolBaseAddress;
}

 _MODULEINFO CUtil::GetModuleInfo(HMODULE hModule) {
	 _MODULEINFO modInfo;
	 GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(_MODULEINFO));
	 return modInfo;
 }


 bool CUtil::Mask(const BYTE* pData, const BYTE* bMask, const char* szMask)
 {
	 for (; *szMask; ++szMask, ++pData, ++bMask)
		 if (*szMask == 'x' && *pData != *bMask)
			 return false;
	 return (*szMask) == NULL;
 }

 DWORD CUtil::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
 {
	 for (DWORD i = 0; i < dwLen; i++)
		 if (this->Mask((BYTE*)(dwAddress + i), bMask, szMask))
			 return (DWORD)(dwAddress + i);
	 return 0;
 }


CUtil* CUtil::Instance()
{
	if (inst == 0)
		inst = new CUtil();
	return inst;
}


