#pragma once

struct Vector {

	float x; float y;
};

class CSceneMgr;
class CObj
{
public:
	CObj();
	CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	CObj(int eType, float fX, float fY, float fZ);
	~CObj();
public:
	ObjInfo*	GetObjInfo() { return &m_tObjInfo; }
	void		SetCollision(bool bColl) { m_bColl = bColl; }
	int			GetLifePoint() { return m_iLifePoint; }
	void		SetLifePoint(int iLife) { m_iLifePoint = iLife; }

	void		SetColor(float fR, float fG, float fB) {
		m_tObjInfo.r = fR; m_tObjInfo.g = fG; m_tObjInfo.b = fB;
	}

public:
	virtual int Update(float fTimeDelta);

protected:
	ObjInfo		m_tObjInfo;
	int			m_eType{ -1 };

	Vector	m_tDir;
	float	m_fSpeed;
	bool	m_bColl{ false };

	float	m_fLifeTime{ 0.f };
	bool	m_bLife{ true };
	int		m_iLifePoint{ 0 };

public:
	void	SetSceneMgr(CSceneMgr* pSceneMgr) { m_pSceneMgr = pSceneMgr; }
protected:
	CSceneMgr* m_pSceneMgr{ nullptr };
};

