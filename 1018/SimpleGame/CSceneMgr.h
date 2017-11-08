#pragma once
#include "Renderer.h"

#include "CObj.h"
#define MAX_OBJECTS_COUNT 50

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

	Renderer *m_pRenderer{ nullptr };
	GLuint m_imageNum[OBJ_END];

public:
	void	Initialize();
	void	RenderObjects(Renderer* pRenderer);

public:
	void	pushObject(OBJ_TYPE eType, CObj* pObject, int nObjNum = -1);
	void	CheckCollsion();
	void	CheckCollisionCharToBuilding();
	void	CheckCollisionCharToBullet();
	void	CheckCollisionBuildingToArrow();
	void	CheckCollisionCharToArrow();

public:
	CObj**	GetObjArray(OBJ_TYPE eType) { return m_ObjArray[eType]; }
	int		GetObjCnt(OBJ_TYPE eType) { return m_iObjCnt[eType]; }

public:
	void	SetRenderer(Renderer* pRenderer) { m_pRenderer = pRenderer; }

};

