#include "stdafx.h"
#include "CObj.h"


CObj::CObj()
{
}

CObj::CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA)
{
	m_tObjInfo.x	= fX;
	m_tObjInfo.y	= fY;
	m_tObjInfo.z	= fZ;
	m_tObjInfo.size = fSize;
	m_tObjInfo.r	= fR;
	m_tObjInfo.g	= fG;
	m_tObjInfo.b	= fB;
	m_tObjInfo.a	= fA;
}


CObj::~CObj()
{
}
