#include "stdafx.h"
#include "CCharacter.h"
#include "CSceneMgr.h"
#include "CArrow.h"

CCharacter::CCharacter(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA)
	:CObj(fX, fY, fZ, fSize, fR, fG, fB, fA)
{
}

CCharacter::CCharacter(int iTeamNum, float fX, float fY, float fZ)
	: CObj(iTeamNum, fX, fY, fZ)
{
	m_pSound = new Sound;
	if (iTeamNum == 0)
	{
		m_iSoundNum = m_pSound->CreateSound("./Sound/char_haeun.wav");
	}
	else
	{
		m_iSoundNum = m_pSound->CreateSound("./Sound/enemy_create.wav");
	}
		m_pSound->PlaySoundW(m_iSoundNum, false, 1.f);

}

CCharacter::~CCharacter()
{
	delete m_pSound;
	m_pSound = nullptr;
}

int CCharacter::Update(float fTimeDelta)
{
	if (m_iLifePoint <= 0)
	{
		return 1;
	}

	if (m_bColl){
		return 1;
	}


	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) m_tDir.y *= -1;


	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;


	m_fArrowCreateAccTime += fTimeDelta;
	if (m_fArrowCreateAccTime > 1.f)	{
		m_fArrowCreateAccTime = 0.f;
		//m_pSceneMgr->pushObject(OBJ_ARROW, new CArrow(3, m_tObjInfo.x, m_tObjInfo.y, 0), this);
		m_pSceneMgr->pushObject(OBJ_ARROW, m_tObjInfo.x, m_tObjInfo.y, m_iTeamNum, this);
	}
	m_fFrameTime += fTimeDelta;
	if (m_fFrameTime > 0.05f)
	{
		m_fFrameTime = 0.f;
		++m_iAnimCnt;
		int nMaxCnt = 0;
		if (m_iTeamNum == 0) nMaxCnt = 5;
		else nMaxCnt = 12;
		if (m_iAnimCnt > nMaxCnt) m_iAnimCnt = 0;
	}

	m_bColl = false;
	return 0;
}

void CCharacter::Render(Renderer * pRenderer)
{
	GLint iImage = -1;
	float fRGB[3];
	if (m_iTeamNum == 0)
	{
		fRGB[0] = 1.f; fRGB[1] = 0.f; fRGB[2] = 0.f;
		iImage = m_pSceneMgr->GetImageNum()[IMAGE_CHAR_MOVE];
	}
	else
	{
		fRGB[0] = 0.f; fRGB[1] = 0.f; fRGB[2] = 1.f;
		iImage = m_pSceneMgr->GetImageNum()[IMAGE_ENEMY_CHAR_MOVE];
	}

	if (m_iTeamNum == 0)
	{
		//pRenderer->DrawSolidRect(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
		//	m_tObjInfo.size,
		//	m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a,
		//	m_tObjInfo.lvType * 0.1f);

		pRenderer->DrawTexturedRectSeq(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
			m_tObjInfo.size,
			m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a, iImage,
			m_iAnimCnt, 0, 5, 1, m_tObjInfo.lvType * 0.1f);
	}
	else
	{
		pRenderer->DrawTexturedRectSeq(m_tObjInfo.x, m_tObjInfo.y, m_tObjInfo.z,
			m_tObjInfo.size,
			m_tObjInfo.r, m_tObjInfo.g, m_tObjInfo.b, m_tObjInfo.a, iImage,
			m_iAnimCnt, 0, 13, 1, m_tObjInfo.lvType * 0.1f);
	}

	pRenderer->DrawSolidRectGauge(m_tObjInfo.x, m_tObjInfo.y + m_tObjInfo.size * 0.7f, m_tObjInfo.z,
		m_tObjInfo.size * 0.9f, m_tObjInfo.size * 0.1f,
		fRGB[0], fRGB[1], fRGB[2], 1.f,
		GetLifeGauge(),
		m_tObjInfo.lvType * 0.1f);
}
