#include "stdafx.h"
#include "CBullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}



CBullet::CBullet(int eType, float fX, float fY, float fZ)
	: CObj(eType, fX, fY, fZ)
{
}
int CBullet::Update(float fTimeDelta)
{
	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) m_tDir.y *= -1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;
	return 0;
}