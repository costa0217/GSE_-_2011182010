#pragma once
#include "Renderer.h"

#include "CObj.h"
#include "Sound.h"
#include "CExBar.h"
#include "CLightning.h"


#define MAX_OBJECTS_COUNT 50

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

private:
	list<CObj*>		m_ObjList[OBJ_END];

	float	m_fAccEnemySummonTime{ 0.f };
	float	m_fAccSummonTime{ 0.f };
	float	m_fAccWeatherTime{ 0.f };
	bool	m_bSummonAble{ true };

	Renderer*	m_pRenderer{ nullptr };
	GLuint		m_imageNum[IMAGE_END];

private:
	Sound*	m_pSound{ nullptr };
	GLuint	m_iSoundNum;

private:
	CExBar*	m_pExBarSys{ nullptr };
	CLightning*	m_pLightning{ nullptr };
	int		m_iPresentIconNum{ -1 };
	int		m_iPretIconNum{ -1 };
public:
	bool	m_bClick{ false };
	float	m_fMouseX{ 0.f };
	float	m_fMouseY{ 0.f };
public:
	GLuint*	GetImageNum() { return m_imageNum; }

public:
	void	Initialize();
	int		Update(float fDeltaTime);
	void	RenderObjects(Renderer* pRenderer);

public:
	void	pushObject(OBJ_TYPE eType, float fPosX, float fPosY, int iTeamNum, CObj* pParent = nullptr);
	void	CreateCharacter(float fPosX, float fPosY);
	void	CreateEnemy(float fTimeDelta);

public:
	void	CheckCollisionCharToBuilding();
	void	CheckCollisionCharToBullet();
	void	CheckCollisionCharToArrow();
	void	CheckCollisionBuildingToArrow();
	void	CheckCollisionBuildingToBullet();

public:
	void	SetRenderer(Renderer* pRenderer) { m_pRenderer = pRenderer; }

};

