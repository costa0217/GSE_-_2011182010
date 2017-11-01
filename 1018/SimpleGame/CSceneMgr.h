#pragma once
#include "Renderer.h"

#include "CObj.h"
#define MAX_OBJECTS_COUNT 10

enum OBJ_TYPE
{
	OBJ_BULDING,
	OBJ_CHARACTER,
	OBJ_BULLET,
	OBJ_ARROW,
	OBJ_END
};

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

private:
	CObj*	m_ObjArray[OBJ_END][MAX_OBJECTS_COUNT];
	int		m_iObjCnt[OBJ_END];

	float	m_fStartTime{ 0.f };
	float	m_fNowTime{ 0.f };

public:
	void	RenderObjects(Renderer* pRenderer);

public:
	void	pushObject(OBJ_TYPE eType, CObj* pObject);
	void	CheckCollsion();
	void	CheckCollisionCharToBuilding();
	void	CheckCollisionCharToBullet();

public:
	CObj**	GetObjArray(OBJ_TYPE eType) { return m_ObjArray[eType]; }
	int		GetObjCnt(OBJ_TYPE eType) { return m_iObjCnt[eType]; }

};

