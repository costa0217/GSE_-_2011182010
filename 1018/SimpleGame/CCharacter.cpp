#include "stdafx.h"
#include "CCharacter.h"
#include "CSceneMgr.h"
#include "CArrow.h"

CCharacter::CCharacter(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA)
	:CObj(fX, fY, fZ, fSize, fR, fG, fB, fA)
{
}

CCharacter::CCharacter(int eType, float fX, float fY, float fZ)
	: CObj(eType, fX, fY, fZ)
{
}

CCharacter::~CCharacter()
{
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
	if (m_fArrowCreateAccTime >0.5f)
	{
		m_fArrowCreateAccTime = 0.f;
		m_pSceneMgr->pushObject(OBJ_ARROW, new CArrow(3, m_tObjInfo.x, m_tObjInfo.y, 0), m_iObjNum);
	}


	m_bColl = false;
	return 0;
}
