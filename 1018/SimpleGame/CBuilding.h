#pragma once
#include "CObj.h"
class CBuilding :
	public CObj
{
public:
	CBuilding();
	CBuilding(int eType, float fX, float fY, float fZ);
	~CBuilding();

public:
	virtual int Update(float fTimeDelta);

private:
	float	m_fBulletCreateAccTime{ 0.f };
};

