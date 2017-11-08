#include "stdafx.h"
#include "CArrow.h"


CArrow::CArrow()
{
}

CArrow::CArrow(int eType, float fX, float fY, float fZ)
	: CObj(eType, fX, fY, fZ)
{
}


CArrow::~CArrow()
{
}

int CArrow::Update(float fTimeDelta)
{
	if (m_bColl)
		return 1;

	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) m_tDir.y *= -1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	return 0;
}
