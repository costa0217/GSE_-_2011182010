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

	m_fSpeed = rand() % 3 + 1.f;

}
CObj::~CObj()
{
}

int CObj::Update(float fTimeDelta)
{
	if (m_tObjInfo.x <= -WINCX * 0.5f || m_tObjInfo.x >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y <= -WINCY * 0.5f || m_tObjInfo.y >= WINCY * 0.5f) m_tDir.y *= -1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	return 0;
}
