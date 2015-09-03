#pragma once

class CUnit;

class CObjectManager
{
public:
	inline CUnit** GetFirst(void) { return m_lpcUnits; }
	inline int GetMaxObjects(void) { return m_dwMaxObjects; }
	inline int GetObjects(void) { return m_dwObjects; }
	inline int GetEnd(void) { return m_dwEnd; }

private:
	/* 0x00 */ CUnit** m_lpcUnits;
	/* 0x04 */ int m_dwMaxObjects;
	/* 0x08 */ int m_dwObjects;
	/* 0x0C */ int m_dwEnd;

	///*0x0*/	cObject** ObjectArray;
	///*0x4*/	int MaxObjects;
	///*0x8*/	int ObjectCount;
	///*0xC*/	int indexLastObject;
};
