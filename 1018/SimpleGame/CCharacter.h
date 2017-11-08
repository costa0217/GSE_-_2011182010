#pragma once
#include "CObj.h"

class CCharacter :
	public CObj
{
public:
	CCharacter(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	CCharacter(int eType, float fX, float fY, float fZ);
	virtual ~CCharacter();

public:
	virtual int Update(float fTimeDelta);

private:
	float	m_fArrowCreateAccTime{ 0.f };


};

