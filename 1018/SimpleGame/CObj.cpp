#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}

CObj::CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA)
{
	m_tObjInfo.x	= fX;	m_tObjInfo.y	= fY;	m_tObjInfo.z	= fZ;
	m_tObjInfo.size = fSize;
	m_tObjInfo.r	= fR;	m_tObjInfo.g	= fG;	m_tObjInfo.b	= fB;	m_tObjInfo.a	= fA;

	m_tDir.x = rand() % 9 - 4;
	m_tDir.y = rand() % 9 - 4;

	if (m_tDir.x == 0.f && m_tDir.y == 0.f)
		m_tDir.x = 1.f;

	float fTemp = sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
	m_tDir.x /= fTemp;
	m_tDir.y /= fTemp;

	m_fSpeed = rand() % 50 + 200.f;

}
CObj::~CObj()
{
}

int CObj::Update(float fTimeDelta)
{
	m_fLifeTime += fTimeDelta;
	if (m_fLifeTime > 10000.f)
	{
		m_bLife = false;
		// µÚÁü
	}
	if (m_bColl){

	}
	else{
		m_tObjInfo.r = 1.f;	m_tObjInfo.g = 1.f;	m_tObjInfo.b = 1.f;	m_tObjInfo.a = 1.f;
	}


	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) m_tDir.y *= -1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	m_bColl = false;
	return 0;
}
