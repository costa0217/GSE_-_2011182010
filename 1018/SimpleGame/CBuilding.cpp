#include "stdafx.h"
#include "CBuilding.h"
#include "CSceneMgr.h"
#include "CBullet.h"

CBuilding::CBuilding()
{
}

CBuilding::CBuilding(int iTeamNum, float fX, float fY, float fZ)
	: CObj(iTeamNum, fX, fY, fZ)
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
	if(m_fBulletCreateAccTime > BULLET_CREATE_TIME)
	{
		m_fBulletCreateAccTime = 0.f;
		m_pSceneMgr->pushObject(OBJ_BULLET, m_tObjInfo.x, m_tObjInfo.y, m_iTeamNum, this);
	}

	return 0;
}
