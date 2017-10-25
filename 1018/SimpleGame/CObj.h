#pragma once

struct Vector {

	float x; float y;
};

class CObj
{
public:
	CObj();
	CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	~CObj();
public:
	ObjInfo*	GetObjInfo() { return &m_tObjInfo; }
	void		SetCollision(bool bColl) { m_bColl = bColl; 
	m_tObjInfo.r = 1.f;	m_tObjInfo.g = 0.f;	m_tObjInfo.b = 0.f;	m_tObjInfo.a = 1.f;
	}

public:
	int Update(float fTimeDelta);

private:
	ObjInfo m_tObjInfo;

	Vector	m_tDir;
	float	m_fSpeed;
	bool	m_bColl{ false };

	float	m_fLifeTime{ 0.f };
	bool	m_bLife{ true };
};

