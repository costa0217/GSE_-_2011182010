#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>

using namespace std;


#define WINCX 500
#define WINCY 500


struct ObjInfo {
	float x; float y; float z;
	float size;
	float r; float g; float b; float a;
};