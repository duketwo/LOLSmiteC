#include "stdafx.h"
#include "Util.h"
#include <sstream>
#include <string>
#include <iomanip>
#include <AtlBase.h>
#include <AtlConv.h>
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;


CUtil* CUtil::inst = 0;

CUtil::CUtil()
{
}


CUtil::~CUtil()
{
	delete CUtil::inst;
}

void CUtil::addLog(char* string)
{
	USES_CONVERSION;
	HANDLE filehandle;
	DWORD dwReadBytes;
	char buffer[2048];
	filehandle = CreateFile(CA2W((getCurrentPath() + "\Log.txt").c_str()), GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0, 0);
	SetFilePointer(filehandle, 0, 0, FILE_END);
	sprintf_s(buffer, 1024, "(%s): %s\r\n", getCurrentDateTime().c_str(), string);
	printf_s("(%s): %s\r\n", getCurrentDateTime().c_str(), string);
	WriteFile(filehandle, buffer, strlen(buffer), &dwReadBytes, 0);
	CloseHandle(filehandle);
}

std::string CUtil::getCurrentPath()
{
	USES_CONVERSION;
	LPTSTR  currentPath = new TCHAR[_MAX_PATH];
	GetModuleFileName((HINSTANCE)&__ImageBase, currentPath, _MAX_PATH);
	std::string currPath = W2A(currentPath);
	currPath.replace(currPath.end() - 12, currPath.end(), "\0");
	return currPath;
}


const std::string CUtil::getCurrentDateTime() 
{
	boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return boost::posix_time::to_simple_string(now);
}


CUtil* CUtil::instance()
{
	if (inst == 0)
		inst = new CUtil();
	return inst;
}
