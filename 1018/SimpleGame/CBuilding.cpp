#include "stdafx.h"
#include "CBuilding.h"
#include "CSceneMgr.h"
#include "CBullet.h"

#pragma warning(disable: 4996) 

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

void CBuilding::Render(Renderer * pRenderer)
{
	GLint imageNum = -1;
	float fRGB[3];
	if (m_iTeamNum == 0)
	{
		imageNum = m_pSceneMgr->GetImageNum()[IMAGE_BUILDING];
		fRGB[0] = 1.f; fRGB[1] = 0.f; fRGB[2] = 0.f;
	}
	else
	{
		imageNum = m_pSceneMgr->GetImageNum()[IMAGE_ENEMY_BUILDING];
		fRGB[0] = 0.f; fRGB[1] = 0.f; fRGB[2] = 1.f;
	}

	pRenderer->DrawTexturedRect(m_tObjInfo.x, m_tObjInfo.y,	m_tObjInfo.z,
		m_tObjInfo.size,
		m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a,
		imageNum,
		m_tObjInfo.lvType * 0.1f);


	char ctemp[40] = "";
	char* pchar = itoa(m_iLifePoint, ctemp, 10);
	pRenderer->DrawText(m_tObjInfo.x, m_tObjInfo.y + m_tObjInfo.size * 0.65f, GLUT_BITMAP_HELVETICA_10, 0.f, 0.f, 0.f, pchar);

	pRenderer->DrawSolidRectGauge(m_tObjInfo.x, m_tObjInfo.y + m_tObjInfo.size * 0.6f, m_tObjInfo.z,
		m_tObjInfo.size * 0.8f, m_tObjInfo.size * 0.08f,
		fRGB[0], fRGB[1], fRGB[2], 1.f,
		GetLifeGauge(),
		m_tObjInfo.lvType * 0.1f);
}
