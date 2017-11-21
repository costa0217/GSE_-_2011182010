#pragma once
#include "CObj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	CBullet(int iTeamNum, float fX, float fY, float fZ);
	~CBullet();

public:
	virtual int Update(float fTimeDelta);
};

