#include "stdafx.h"
#include "CBullet.h"
#include "CSceneMgr.h"

CBullet::CBullet()
{
	m_fParticleAccTime = 0;
}


CBullet::~CBullet()
{
	m_fParticleAccTime = 0;
}



CBullet::CBullet(int iTeamNum, float fX, float fY, float fZ)
	: CObj(iTeamNum, fX, fY, fZ)
{
}
int CBullet::Update(float fTimeDelta)
{
	if (m_bColl)
		return 1;

	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) return 1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) return 1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	m_fParticleAccTime += fTimeDelta;
	return 0;
}

void CBullet::Render(Renderer * pRenderer)
{
	GLint iImage = m_pSceneMgr->GetImageNum()[IMAGE_BULLET_PARTICLE];

	pRenderer->DrawParticle(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
		m_tObjInfo.size * 2.f,
		1.f, 1.f, 1.f, 1.f, -m_tDir.x, -m_tDir.y, iImage, m_fParticleAccTime, m_tObjInfo.lvType * 0.1f);

	pRenderer->DrawSolidRect(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
		m_tObjInfo.size,
		m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a,
		m_tObjInfo.lvType * 0.1f);



}
