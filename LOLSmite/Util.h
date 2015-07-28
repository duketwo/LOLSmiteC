#pragma once
#include <string>
class CUtil
{
public:
	static CUtil* instance();
	void addLog(char* string);
	std::string CUtil::getCurrentPath();
	const std::string CUtil::getCurrentDateTime();
protected:
	CUtil();
private:
	static CUtil *inst;
	~CUtil();
};


