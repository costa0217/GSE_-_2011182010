#include "stdafx.h"
#include "CCharacter.h"


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
	m_fLifeTime += fTimeDelta;
	if (m_fLifeTime > 10000.f)
	{
		m_bLife = false;
		// µÚÁü
	}
	if (m_bColl){
		return 1;
	}


	if (m_tObjInfo.x - m_tObjInfo.size * 0.5f <= -WINCX * 0.5f || m_tObjInfo.x + m_tObjInfo.size * 0.5f >= WINCX * 0.5f) m_tDir.x *= -1;
	if (m_tObjInfo.y - m_tObjInfo.size * 0.5f <= -WINCY * 0.5f || m_tObjInfo.y + m_tObjInfo.size * 0.5f >= WINCY * 0.5f) m_tDir.y *= -1;

	m_tObjInfo.x += m_tDir.x * m_fSpeed * fTimeDelta;
	m_tObjInfo.y += m_tDir.y * m_fSpeed * fTimeDelta;

	m_bColl = false;
	return 0;
}
