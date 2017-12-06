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

#include "Define.h"

using namespace std;


#define WINCX 500
#define WINCY 800


enum OBJ_TYPE
{
	OBJ_BULDING,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_ARROW,
	OBJ_END
};

enum IMAGE_TYPE 
{
	IMAGE_BUILDING,
	IMAGE_ENEMY_BUILDING,
	IMAGE_ENEMY_CHAR_MOVE,
	IMAGE_CHAR_MOVE,
	IMAGE_BULLET_PARTICLE,
	IMAGE_BACKGROUND,
	
	IMAGE_END,
};

enum RENDER_LEVEL_TYPE
{
	LEVEL_GOD,
	LEVEL_SKY,
	LEVEL_GROUND,
	LEVEL_UNDERGROUND,
	LEVEL_END
};

struct ObjInfo {
	float x; float y; float z;
	float size;
	float r; float g; float b; float a;
	RENDER_LEVEL_TYPE lvType;
};