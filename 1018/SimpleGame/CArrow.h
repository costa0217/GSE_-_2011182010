#pragma once
#include "CObj.h"
class CArrow :
	public CObj
{
public:
	CArrow();
	CArrow(int eType, float fX, float fY, float fZ);
	~CArrow();


public:
	virtual int Update(float fTimeDelta);
};
