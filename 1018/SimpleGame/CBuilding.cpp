#include "stdafx.h"
#include "CBuilding.h"
#include "CSceneMgr.h"
#include "CBullet.h"

CBuilding::CBuilding()
{
}

CBuilding::CBuilding(int eType, float fX, float fY, float fZ)
	: CObj(eType, fX, fY, fZ)
{
}

CBuilding::~CBuilding()
{
}

int CBuilding::Update(float fTimeDelta)
{
	if (m_iLifePoint <= 0)
	{
		return 1;
	}

	
	m_fBulletCreateAccTime += fTimeDelta;
	if(m_fBulletCreateAccTime >0.5f)
	{
		m_fBulletCreateAccTime = 0.f;
		m_pSceneMgr->pushObject(OBJ_BULLET, new CBullet(2, 0, 0, 0));
	}

	return 0;
}
