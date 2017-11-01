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

	m_tDir.x = float(rand() % 9 - 4);
	m_tDir.y = float(rand() % 9 - 4);

	if (m_tDir.x == 0.f && m_tDir.y == 0.f)
		m_tDir.x = 1.f;

	float fTemp = sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
	m_tDir.x /= fTemp;
	m_tDir.y /= fTemp;

	m_fSpeed = rand() % 50 + 200.f;

}
CObj::CObj(int eType, float fX, float fY, float fZ)
{
	m_eType = eType;
	m_tObjInfo.x = fX;	m_tObjInfo.y = fY;	m_tObjInfo.z = fZ;
	switch (eType)
	{
	case 0:
		m_tObjInfo.size = 10;
		m_tObjInfo.r = 1;	m_tObjInfo.g = 1;	m_tObjInfo.b = 1;	m_tObjInfo.a = 1;

		m_tDir.x = float(rand() % 9 - 4);
		m_tDir.y = float(rand() % 9 - 4);

		if (m_tDir.x == 0.f && m_tDir.y == 0.f)
			m_tDir.x = 1.f;

		//float fTemp = sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
		m_tDir.x /= sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
		m_tDir.y /= sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));

		m_fSpeed = 100.f;
		m_iLifePoint = 10;
		break;
	case 1:
		m_tObjInfo.size = 50;
		m_tObjInfo.r = 1;	m_tObjInfo.g = 1;	m_tObjInfo.b = 0;	m_tObjInfo.a = 1;

		m_iLifePoint = 100;
		break;
	case 2:
		m_tDir.x = float(rand() % 9 - 4);
		m_tDir.y = float(rand() % 9 - 4);

		if (m_tDir.x == 0.f && m_tDir.y == 0.f)
			m_tDir.x = 1.f;

		//float fTemp = sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
		m_tDir.x /= sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));
		m_tDir.y /= sqrtf(pow(m_tDir.x, 2) + pow(m_tDir.y, 2));

		m_tObjInfo.size = 4;
		m_tObjInfo.r = 1;	m_tObjInfo.g = 0;	m_tObjInfo.b = 0;	m_tObjInfo.a = 1;
		m_fSpeed = 300.f;
		m_iLifePoint = 300;
		break;
	case 3:
		m_tObjInfo.size = 4;
		m_tObjInfo.r = 0;	m_tObjInfo.g = 1;	m_tObjInfo.b = 0;	m_tObjInfo.a = 1;
		break;

	}
}
CObj::~CObj()
{
}

int CObj::Update(float fTimeDelta)
{
	return 0;
}
