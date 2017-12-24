#include "stdafx.h"
#include "CSceneMgr.h"
#include "CBuilding.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CArrow.h"

CSceneMgr::CSceneMgr()
{
}

CSceneMgr::~CSceneMgr()
{
//	for (int i = 0; i < OBJ_END; ++i)
//	{
//		for (int j = 0; j < m_iObjCnt[i]; ++j)
//		{
//			delete m_ObjArray[i][j];
//			m_ObjArray[i][j] = nullptr;
//		}
//	}
	delete m_pExBarSys;
	m_pExBarSys = nullptr;
	delete m_pLightning;
	m_pLightning = nullptr;
}

void CSceneMgr::pushObject(OBJ_TYPE eType, float fPosX, float fPosY, int iTeamNum, CObj * pParent)
{
	CObj* pObject = nullptr;
	int iLimitCnt = -1;

	switch (eType)
	{
	case OBJ_BULDING:
		pObject = new CBuilding(iTeamNum, fPosX, fPosY, 0.f);
		pObject->SetColor(1.f, 1.f, 1.f);

		pObject->SetSceneMgr(this);
		pObject->SetLifePoint(BUILDING_LIFE, -1);
		pObject->SetSpeed(BUILDING_SPEED);
		pObject->SetSize(BUILDING_SIZE);
		pObject->SetRenderLevel(LEVEL_SKY);

		iLimitCnt = 6;
		break;
	case OBJ_CHARACTER:
		pObject = new CCharacter(iTeamNum, fPosX, fPosY, 0.f);
		if (iTeamNum == 0){
			pObject->SetColor(1.f, 0.f, 0.f);
		}else if (iTeamNum == 1) {
			pObject->SetColor(0.f, 0.f, 1.f);
		}
		pObject->SetSceneMgr(this);
		pObject->SetLifePoint(CHARACTER_LIFE, -1);
		pObject->SetSpeed(CHARACTER_SPEED);
		pObject->SetSize(CHARACTER_SIZE);
		pObject->SetRenderLevel(LEVEL_GROUND);

		iLimitCnt = 10;
		break;
	case OBJ_BULLET:
		pObject = new CBullet(iTeamNum, fPosX, fPosY, 0.f);
		if (iTeamNum == 0) {
			pObject->SetColor(1.f, 0.f, 0.f);
		}
		else if (iTeamNum == 1) {
			pObject->SetColor(0.f, 0.f, 1.f);
		}
		pObject->SetSceneMgr(this);
		pObject->SetParent(pParent);
		pObject->SetLifePoint(BULLET_LIFE, -1);
		pObject->SetSpeed(BULLET_SPEED);
		pObject->SetSize(BULLET_SIZE);
		pObject->SetRenderLevel(LEVEL_UNDERGROUND);

		iLimitCnt = 30;
		break;
	case OBJ_ARROW:
		pObject = new CArrow(iTeamNum, fPosX, fPosY, 0.f);
		if (iTeamNum == 0) {
			pObject->SetColor(0.5f, 0.2f, 0.7f);
		}
		else if (iTeamNum == 1) {
			pObject->SetColor(1.f, 1.f, 0.f);
		}
		pObject->SetSceneMgr(this);
		pObject->SetParent(pParent);
		pObject->SetLifePoint(ARROW_LIFE, -1);
		pObject->SetSpeed(ARROW_SPEED);
		pObject->SetSize(ARROW_SIZE);
		pObject->SetRenderLevel(LEVEL_UNDERGROUND);

		iLimitCnt = 100;
		break;
	}

	if (iLimitCnt > m_ObjList[eType].size())
	{
		m_ObjList[eType].emplace_back(pObject);
	}
}

void CSceneMgr::CreateCharacter(float fPosX, float fPosY)
{
	m_iPresentIconNum = m_pExBarSys->PushIcon(fPosX, fPosY);
	if (-1 != m_iPresentIconNum)
	{
		m_bClick = true;
	}
	else
	{
		if (true == m_bClick)
		{
			switch (m_iPretIconNum)
			{
			case 0:
				if (fPosY > -271.f && fPosY < 7.f)
				{
					pushObject(OBJ_CHARACTER, fPosX, fPosY, 0);
					m_pExBarSys->ProcessIcon(m_iPretIconNum);
				}
				break;
			case 1:
				if (fPosY > -271.f && fPosY < 7.f)
				{
					pushObject(OBJ_CHARACTER, fPosX, fPosY, 0);
					m_pExBarSys->ProcessIcon(m_iPretIconNum);
				}
				break;
			case 2:
				m_pExBarSys->ProcessIcon(m_iPretIconNum);
				break;
			case 3:
				m_pExBarSys->ProcessIcon(m_iPretIconNum);
				m_pLightning->m_fPosX = fPosX;
				m_pLightning->m_fPosY = fPosY;
				m_pLightning->m_bAble = true;
				break;
			case 4:
				//m_pExBarSys->ProcessIcon(m_iPretIconNum);
				break;
			}
		}
		m_bClick = false;
	}
	m_iPretIconNum = m_iPresentIconNum;
	//if (fPosY > WINCY * -0.5f && fPosY < 0.f)
	//{
	//	if (true == m_bSummonAble)
	//	{
	//		m_fAccSummonTime = 0.f;
	//		m_bSummonAble = false;
	//		pushObject(OBJ_CHARACTER, fPosX, fPosY, 0);
	//	}
	//}	
}

void CSceneMgr::CreateEnemy(float fTimeDelta)
{
	m_fAccEnemySummonTime += fTimeDelta;
	if (m_fAccEnemySummonTime > ENEMY_CHARACTE_CREATE_TIME)
	{
		m_fAccEnemySummonTime = 0.f;
		pushObject(OBJ_CHARACTER, float(rand() % WINCX - int(WINCX *0.4f)), float(rand() % int(WINCY *0.4f)), 1);
	}
}

void CSceneMgr::CheckCollisionCharToBuilding()
{
	list<CObj*>::iterator B_iter = m_ObjList[OBJ_BULDING].begin();
	list<CObj*>::iterator B_iter_end = m_ObjList[OBJ_BULDING].end();
	for (; B_iter != B_iter_end; ++B_iter)
	{
		list<CObj*>::iterator C_iter = m_ObjList[OBJ_CHARACTER].begin();
		list<CObj*>::iterator C_iter_end = m_ObjList[OBJ_CHARACTER].end();
		for (; C_iter != C_iter_end; ++C_iter)
		{
			if ((*B_iter)->GetTeamNum() == (*C_iter)->GetTeamNum()) continue;
			
			ObjInfo* pBuilding = (*B_iter)->GetObjInfo();
			ObjInfo* pCharacter = (*C_iter)->GetObjInfo();

			if (pBuilding->x - pBuilding->size * 0.5f	< pCharacter->x + pCharacter->size * 0.5f &&
				pBuilding->y - pBuilding->size * 0.5f	< pCharacter->y + pCharacter->size * 0.5f &&
				pBuilding->x + pBuilding->size * 0.5f	> pCharacter->x - pCharacter->size * 0.5f &&
				pBuilding->y + pBuilding->size * 0.5f	> pCharacter->y - pCharacter->size * 0.5f)
			{
				(*B_iter)->SetLifePoint((*B_iter)->GetLifePoint() - (*C_iter)->GetLifePoint());
				(*C_iter)->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionCharToBullet()
{
	list<CObj*>::iterator C_iter = m_ObjList[OBJ_CHARACTER].begin();
	list<CObj*>::iterator C_iter_end = m_ObjList[OBJ_CHARACTER].end();
	for (; C_iter != C_iter_end; ++C_iter)
	{
		list<CObj*>::iterator B_iter = m_ObjList[OBJ_BULLET].begin();
		list<CObj*>::iterator B_iter_end = m_ObjList[OBJ_BULLET].end();
		for (; B_iter != B_iter_end; ++B_iter)
		{
			if ((*B_iter)->GetTeamNum() == (*C_iter)->GetTeamNum()) continue;

			ObjInfo* pCharacter = (*C_iter)->GetObjInfo();
			ObjInfo* pBullet = (*B_iter)->GetObjInfo();

			if (pBullet->x - pBullet->size * 0.5f	< pCharacter->x + pCharacter->size * 0.5f &&
				pBullet->y - pBullet->size * 0.5f	< pCharacter->y + pCharacter->size * 0.5f &&
				pBullet->x + pBullet->size * 0.5f	> pCharacter->x - pCharacter->size * 0.5f &&
				pBullet->y + pBullet->size * 0.5f	> pCharacter->y - pCharacter->size * 0.5f)
			{
				(*C_iter)->SetLifePoint((*C_iter)->GetLifePoint() - (*B_iter)->GetLifePoint());
				(*B_iter)->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionBuildingToArrow()
{

	/*for (int i = 0; i < m_iObjCnt[OBJ_BULDING]; ++i)
	{
		m_ObjArray[OBJ_BULDING][i]->SetColor(1.f, 1.f, 0.f);
		for (int j = 0; j < m_iObjCnt[OBJ_ARROW]; ++j)
		{
			ObjInfo* pBuilding = m_ObjArray[OBJ_BULDING][i]->GetObjInfo();
			ObjInfo* pArrow = m_ObjArray[OBJ_ARROW][j]->GetObjInfo();


			if (pBuilding->x - pBuilding->size * 0.5f	< pArrow->x + pArrow->size * 0.5f &&
				pBuilding->y - pBuilding->size * 0.5f	< pArrow->y + pArrow->size * 0.5f &&
				pBuilding->x + pBuilding->size * 0.5f	> pArrow->x - pArrow->size * 0.5f &&
				pBuilding->y + pBuilding->size * 0.5f	> pArrow->y - pArrow->size * 0.5f)
			{
				m_ObjArray[OBJ_BULDING][i]->SetLifePoint(m_ObjArray[OBJ_BULDING][i]->GetLifePoint() - m_ObjArray[OBJ_ARROW][j]->GetLifePoint());
				m_ObjArray[OBJ_BULDING][i]->SetColor(1.f, 0.f, 0.f);
				m_ObjArray[OBJ_ARROW][j]->SetCollision(true);
			}
		}
	}*/
	list<CObj*>::iterator B_iter = m_ObjList[OBJ_BULDING].begin();
	list<CObj*>::iterator B_iter_end = m_ObjList[OBJ_BULDING].end();
	for (; B_iter != B_iter_end; ++B_iter)
	{
		list<CObj*>::iterator A_iter = m_ObjList[OBJ_ARROW].begin();
		list<CObj*>::iterator A_iter_end = m_ObjList[OBJ_ARROW].end();
		for (; A_iter != A_iter_end; ++A_iter)
		{
			if ((*A_iter)->GetTeamNum() == (*B_iter)->GetTeamNum()) continue;

			ObjInfo* pBuilding = (*B_iter)->GetObjInfo();
			ObjInfo* pArrow = (*A_iter)->GetObjInfo();

			if (pArrow->x - pArrow->size * 0.5f	< pBuilding->x + pBuilding->size * 0.5f &&
				pArrow->y - pArrow->size * 0.5f	< pBuilding->y + pBuilding->size * 0.5f &&
				pArrow->x + pArrow->size * 0.5f	> pBuilding->x - pBuilding->size * 0.5f &&
				pArrow->y + pArrow->size * 0.5f	> pBuilding->y - pBuilding->size * 0.5f)
			{
				(*B_iter)->SetLifePoint((*B_iter)->GetLifePoint() - (*A_iter)->GetLifePoint());
				(*A_iter)->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionBuildingToBullet()
{
	list<CObj*>::iterator B_iter = m_ObjList[OBJ_BULDING].begin();
	list<CObj*>::iterator B_iter_end = m_ObjList[OBJ_BULDING].end();
	for (; B_iter != B_iter_end; ++B_iter)
	{
		list<CObj*>::iterator Bul_iter = m_ObjList[OBJ_ARROW].begin();
		list<CObj*>::iterator Bul_iter_end = m_ObjList[OBJ_ARROW].end();
		for (; Bul_iter != Bul_iter_end; ++Bul_iter)
		{
			if ((*Bul_iter)->GetTeamNum() == (*B_iter)->GetTeamNum()) continue;

			ObjInfo* pBuilding = (*B_iter)->GetObjInfo();
			ObjInfo* pBullet = (*Bul_iter)->GetObjInfo();

			if (pBullet->x - pBullet->size * 0.5f	< pBuilding->x + pBuilding->size * 0.5f &&
				pBullet->y - pBullet->size * 0.5f	< pBuilding->y + pBuilding->size * 0.5f &&
				pBullet->x + pBullet->size * 0.5f	> pBuilding->x - pBuilding->size * 0.5f &&
				pBullet->y + pBullet->size * 0.5f	> pBuilding->y - pBuilding->size * 0.5f)
			{
				(*B_iter)->SetLifePoint((*B_iter)->GetLifePoint() - (*Bul_iter)->GetLifePoint());
				(*Bul_iter)->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionCharToArrow()
{
	list<CObj*>::iterator C_iter = m_ObjList[OBJ_CHARACTER].begin();
	list<CObj*>::iterator C_iter_end = m_ObjList[OBJ_CHARACTER].end();
	for (; C_iter != C_iter_end; ++C_iter)
	{
		list<CObj*>::iterator A_iter = m_ObjList[OBJ_ARROW].begin();
		list<CObj*>::iterator A_iter_end = m_ObjList[OBJ_ARROW].end();
		for (; A_iter != A_iter_end; ++A_iter)
		{
			if ((*A_iter)->GetTeamNum() == (*C_iter)->GetTeamNum()) continue;

			ObjInfo* pCharacter = (*C_iter)->GetObjInfo();
			ObjInfo* pArrow = (*A_iter)->GetObjInfo();

			if (pArrow->x - pArrow->size * 0.5f	< pCharacter->x + pCharacter->size * 0.5f &&
				pArrow->y - pArrow->size * 0.5f	< pCharacter->y + pCharacter->size * 0.5f &&
				pArrow->x + pArrow->size * 0.5f	> pCharacter->x - pCharacter->size * 0.5f &&
				pArrow->y + pArrow->size * 0.5f	> pCharacter->y - pCharacter->size * 0.5f)
			{
				(*C_iter)->SetLifePoint((*C_iter)->GetLifePoint() - (*A_iter)->GetLifePoint());
				(*A_iter)->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::Initialize()
{
	m_imageNum[IMAGE_BUILDING] = m_pRenderer->CreatePngTexture("./Textures/Building.png");
	m_imageNum[IMAGE_ENEMY_BUILDING] = m_pRenderer->CreatePngTexture("./Textures/enemy_building.png");

	m_imageNum[IMAGE_ENEMY_CHAR_MOVE] = m_pRenderer->CreatePngTexture("./Textures/Enemy_Move_13.png");
	m_imageNum[IMAGE_CHAR_MOVE] = m_pRenderer->CreatePngTexture("./Textures/My_Move_5.png");
	m_imageNum[IMAGE_BULLET_PARTICLE] = m_pRenderer->CreatePngTexture("./Textures/Particle.png");

	m_imageNum[IMAGE_BACKGROUND] = m_pRenderer->CreatePngTexture("./Textures/background.png");
	m_imageNum[IMAGE_SNOW] = m_pRenderer->CreatePngTexture("./Textures/snow.png");

	m_imageNum[IMAGE_EXBAR] = m_pRenderer->CreatePngTexture("./Textures/ExBar.png");
	m_imageNum[IMAGE_EXPOINT] = m_pRenderer->CreatePngTexture("./Textures/ExPoint.png");
	m_imageNum[IMAGE_EX] = m_pRenderer->CreatePngTexture("./Textures/elixer.png");
	m_imageNum[IMAGE_NUMBER] = m_pRenderer->CreatePngTexture("./Textures/Number.png");

	m_pExBarSys = new CExBar;
	m_pExBarSys->GetImageNum(m_imageNum[IMAGE_EXBAR], m_imageNum[IMAGE_EX], m_imageNum[IMAGE_EXPOINT], m_imageNum[IMAGE_NUMBER]);


	GLint wndicon[5];
	
	m_imageNum[IMAGE_WND] = m_pRenderer->CreatePngTexture("./Textures/window.png");
	wndicon[0] = m_imageNum[IMAGE_WNDICON1] = m_pRenderer->CreatePngTexture("./Textures/1.png");
	wndicon[1] = m_imageNum[IMAGE_WNDICON2] = m_pRenderer->CreatePngTexture("./Textures/2.png");
	wndicon[2] = m_imageNum[IMAGE_WNDICON3] = m_pRenderer->CreatePngTexture("./Textures/3.png");
	wndicon[3] = m_imageNum[IMAGE_WNDICON4] = m_pRenderer->CreatePngTexture("./Textures/4.png");
	wndicon[4] = m_imageNum[IMAGE_WNDICON5] = m_pRenderer->CreatePngTexture("./Textures/5.png");
	m_pExBarSys->GetWndImgNum(wndicon, m_imageNum[IMAGE_WND]);

	m_imageNum[IMAGE_RellyPoint] = m_pRenderer->CreatePngTexture("./Textures/RellyPoint.png");

	m_imageNum[IMAGE_Lightning] = m_pRenderer->CreatePngTexture("./Textures/Lightning.png");

	m_pLightning = new CLightning;
	m_pLightning->m_iImage = m_imageNum[IMAGE_Lightning];

	pushObject(OBJ_BULDING, 0.f, -237.f, 0);
	pushObject(OBJ_BULDING, -132.f, -160.f, 0);
	pushObject(OBJ_BULDING, 132.f, -160.f, 0);

	pushObject(OBJ_BULDING, 0.f, 297.f, 1);
	pushObject(OBJ_BULDING, -132.f, 230.f, 1);
	pushObject(OBJ_BULDING, 132.f, 230.f, 1);

	m_pSound = new Sound;
	m_iSoundNum = m_pSound->CreateSound("./Sound/BGM.wav");
	m_pSound->PlaySoundW(m_iSoundNum, true, 1.f);
}
int CSceneMgr::Update(float fDeltaTime)
{
	//if (false == m_bSummonAble)
	//{
	//	m_fAccSummonTime += fDeltaTime;
	//	if (m_fAccSummonTime > CHARACTE_CREATE_TIME)
	//	{
	//		m_bSummonAble = true;
	//		m_fAccSummonTime = 0.f;
	//	}
	//}	
	m_fAccWeatherTime += fDeltaTime;
	CreateEnemy(fDeltaTime);

	m_pExBarSys->Update(fDeltaTime);
	m_pLightning->Update(fDeltaTime);

	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		list<CObj*>::iterator iter_end = m_ObjList[i].end();
		for (; iter != iter_end; )
		{
			if (1 == (*iter)->Update(fDeltaTime))
			{
				if (nullptr != (*iter)){
					delete (*iter);
					(*iter) = nullptr;
				}
				iter = m_ObjList[i].erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	return 0;
}
void CSceneMgr::RenderObjects(Renderer * pRenderer)
{
	//CheckCollsion();
	CheckCollisionCharToBuilding();
	CheckCollisionCharToBullet();
	CheckCollisionCharToArrow();
	CheckCollisionBuildingToArrow();
	CheckCollisionBuildingToBullet();

	m_pRenderer->DrawTexturedRectXY(0.f, 0.f, 0.f,
		WINCX,
		WINCY,
		1.f, 1.f, 1.f, 1.f,
		m_imageNum[IMAGE_BACKGROUND],
		0.9f);
	m_pRenderer->DrawParticleClimate(0.f, 0.f, 0.f
		, 1.f,
		1.f, 1.f, 1.f, 1.f,
		sinf(m_fAccWeatherTime * 0.5f),
		abs(cosf(m_fAccWeatherTime) + 1.5f) * -0.4f
		, m_imageNum[IMAGE_SNOW], m_fAccWeatherTime, 0.05f);
	//m_pRenderer->DrawText(WINCX * -0.45f, WINCY * 0.45f, GLUT_BITMAP_9_BY_15, 1.f, 1.f, 0.f, "Kingdom Royale");


	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		list<CObj*>::iterator iter_end = m_ObjList[i].end();
		for (; iter != iter_end; ++iter)
		{
			(*iter)->Render(m_pRenderer);
		}
	}

	if (m_bClick)
	{
		m_pRenderer->DrawTexturedRectXY(m_fMouseX, m_fMouseY, 0.f,
			30.f,
			20.f,
			1.f, 1.f, 1.f, 1.f,
			m_imageNum[IMAGE_RellyPoint],
			0.01f);
	}
	m_pLightning->Render(m_pRenderer);
	m_pExBarSys->Render(m_pRenderer);

}
