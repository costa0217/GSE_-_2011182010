#include "stdafx.h"
#include "CArrow.h"


CArrow::CArrow()
{
}

CArrow::CArrow(int iTeamNum, float fX, float fY, float fZ)
	: CObj(iTeamNum, fX, fY, fZ)
{
}


CArrow::~CArrow()
{
}

int CArrow::Update(float fTimeDelta)
{
	if (m_bColl)
		return 1;

	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) return 1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) return 1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	return 0;
}

void CArrow::Render(Renderer * pRenderer)
{
	pRenderer->DrawSolidRect(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
		m_tObjInfo.size,
		m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a,
		m_tObjInfo.lvType * 0.1f);
}
