#pragma once
#include "CObj.h"

class CCharacter :
	public CObj
{
public:
	CCharacter(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	CCharacter(int iTeamNum, float fX, float fY, float fZ);
	virtual ~CCharacter();

public:
	virtual int Update(float fTimeDelta);
	virtual void Render(Renderer* pRenderer);

private:
	float	m_fArrowCreateAccTime{ 0.f };

	float	m_fFrameTime{ 0.f };

	int		m_iAnimCnt{ 0 };


};

