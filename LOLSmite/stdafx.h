// stdafx.h: Includedatei f�r Standardsystem-Includedateien
// oder h�ufig verwendete projektspezifische Includedateien,
// die nur in unregelm��igen Abst�nden ge�ndert werden.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschlie�en
// Windows-Headerdateien:
#include <windows.h>
#define _CRT_NON_CONFORMING_SWPRINTFS
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <AtlBase.h>
#include <AtlConv.h>
#include <chrono>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Psapi.h>
#include <iostream>

#define DPRINT __noop

#include "Unit.h"
//#include "LOLOffsets.h"
#include "Memory.h"
#include "Core.h"
#include "Util.h"
#include "DX9Hook.h"
#include "Offset.h"

// TODO: Hier auf zus�tzliche Header, die das Programm erfordert, verweisen.
