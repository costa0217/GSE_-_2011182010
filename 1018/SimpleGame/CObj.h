#pragma once

#include "Renderer.h"

struct Vector {

	float x; float y;
};


class CSceneMgr;
class CObj
{
public:
	CObj();
	CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	CObj(int iTeamNum, float fX, float fY, float fZ);
	~CObj();
public:
	ObjInfo*	GetObjInfo() { return &m_tObjInfo; }
	void		SetCollision(bool bColl) { m_bColl = bColl; }
	int			GetLifePoint() { return m_iLifePoint; }
	void		SetLifePoint(int iLife, int iInit = 0) { if (iInit != 0) m_iLifeMaxPoint = iLife; m_iLifePoint = iLife; }
	float		GetLifeGauge() {return (float(m_iLifePoint)	/ float(m_iLifeMaxPoint));}

	//void		SetObjNum(int n) { m_iObjNum = n; }
	//int			GetObjNum() { return m_iObjNum; }

	int			GetTeamNum() {	return m_iTeamNum;	}

	void		SetColor(float fR, float fG, float fB) {m_tObjInfo.r = fR; m_tObjInfo.g = fG; m_tObjInfo.b = fB;}
	void		SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }
	void		SetSize(float fSize) { m_tObjInfo.size = fSize; }
	void		SetRenderLevel(RENDER_LEVEL_TYPE iLvl) { m_tObjInfo.lvType = RENDER_LEVEL_TYPE(iLvl); }

public:
	virtual int Update(float fTimeDelta);
	virtual void Render(Renderer* pRenderer);

protected:
	ObjInfo		m_tObjInfo;

	Vector		m_tDir;
	float		m_fSpeed;
	bool		m_bColl{ false };

	float		m_fLifeTime{ 0.f };
	bool		m_bLife{ true };
	int			m_iLifePoint{ 0 };
	int			m_iLifeMaxPoint{ 0 };

protected:
	CObj*		m_pParent{ nullptr };
	int			m_iTeamNum{ -1 };

public:
	void		SetSceneMgr(CSceneMgr* pSceneMgr) { m_pSceneMgr = pSceneMgr; }
	void		SetParent(CObj* pParent) { m_pParent = pParent; }
protected:
	CSceneMgr* m_pSceneMgr{ nullptr };
};

