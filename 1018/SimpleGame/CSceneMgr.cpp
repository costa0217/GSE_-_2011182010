#include "stdafx.h"
#include "CSceneMgr.h"
#include "CBuilding.h"
#include "CCharacter.h"
#include "CBullet.h"
#include "CArrow.h"

CSceneMgr::CSceneMgr()
{
	//m_fStartTime = (float)timeGetTime() * 0.001f;   //√ ¥‹¿ß∑Œ πŸ≤„¡‹
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
}

//void CSceneMgr::pushObject(OBJ_TYPE eType, CObj * pObject, int nObjNum)
//{
	//if (m_iObjCnt[eType] == MAX_OBJECTS_COUNT) return;


	//m_ObjArray[eType][m_iObjCnt[eType]] = pObject;
	//m_ObjArray[eType][m_iObjCnt[eType]]->SetSceneMgr(this);

	//if (-1 != nObjNum)
	//{
	//	m_ObjArray[eType][m_iObjCnt[eType]]->SetObjNum(nObjNum);
	//}
	//else
	//{
	//	m_ObjArray[eType][m_iObjCnt[eType]]->SetObjNum(m_iObjCnt[eType]);
	//}

	//++m_iObjCnt[eType];
//}

void CSceneMgr::pushObject(OBJ_TYPE eType, float fPosX, float fPosY, int iTeamNum, CObj * pParent)
{
	CObj* pObject = nullptr;
	int iLimitCnt = -1;

	switch (eType)
	{
	case OBJ_BULDING:
		pObject = new CBuilding(iTeamNum, fPosX, fPosY, 0.f);
		pObject->SetLifePoint(BUILDING_LIFE);
		pObject->SetSceneMgr(this);
		pObject->SetSpeed(BUILDING_SPEED);
		pObject->SetSize(BUILDING_SIZE);

		iLimitCnt = 6;
		break;
	case OBJ_CHARACTER:
		pObject = new CCharacter(iTeamNum, fPosX, fPosY, 0.f);
		if (iTeamNum == 0){
			pObject->SetColor(1.f, 0.f, 0.f);
		}else if (iTeamNum == 1) {
			pObject->SetColor(0.f, 0.f, 1.f);
		}
		pObject->SetLifePoint(CHARACTER_LIFE);
		pObject->SetSceneMgr(this);
		pObject->SetSpeed(CHARACTER_SPEED);
		pObject->SetSize(CHARACTER_SIZE);

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
		pObject->SetLifePoint(BULLET_LIFE);
		pObject->SetSceneMgr(this);
		pObject->SetSpeed(BULLET_SPEED);
		pObject->SetParent(pParent);
		pObject->SetSize(BULLET_SIZE);

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
		pObject->SetLifePoint(ARROW_LIFE);
		pObject->SetSceneMgr(this);
		pObject->SetSpeed(ARROW_SPEED);
		pObject->SetParent(pParent);
		pObject->SetSize(ARROW_SIZE);

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
	//printf("%f, %f\n", fPosX, fPosY);

	if (fPosY > WINCY * -0.5f && fPosY < 0.f)
	{
		if (true == m_bSummonAble)
		{
			m_fAccSummonTime = 0.f;
			m_bSummonAble = false;
			pushObject(OBJ_CHARACTER, fPosX, fPosY, 0);
		}
	}	
}

void CSceneMgr::CreateEnemy(float fTimeDelta)
{
	m_fAccEnemySummonTime += fTimeDelta;
	if (m_fAccEnemySummonTime > ENEMY_CHARACTE_CREATE_TIME)
	{
		m_fAccEnemySummonTime = 0.f;
		pushObject(OBJ_CHARACTER, float(rand() % WINCX - int(WINCX *0.5f)), float(rand() % int(WINCY *0.5f)), 1);
	}
}

void CSceneMgr::CheckCollsion()
{
	// √Êµπ∑Œ¡˜ ¿œµ˝ x
	//for (int i = 0; i < m_iObjCnt; ++i)
	//{
	//	for (int j = i; j < m_iObjCnt; ++j)
	//	{
	//		if (i == j) continue;

	//		ObjInfo* pRect1 = m_ObjArray[i]->GetObjInfo();
	//		ObjInfo* pRect2 = m_ObjArray[j]->GetObjInfo();

	//		if (pRect1->x - pRect1->size * 0.5f	< pRect2->x + pRect2->size * 0.5f &&
	//			pRect1->y - pRect1->size * 0.5f < pRect2->y + pRect2->size * 0.5f &&
	//			pRect1->x + pRect1->size * 0.5f > pRect2->x - pRect2->size * 0.5f &&
	//			pRect1->y + pRect1->size * 0.5f > pRect2->y - pRect2->size * 0.5f)
	//		{
	//			m_ObjArray[i]->SetCollision(true);
	//			m_ObjArray[j]->SetCollision(true);
	//		}
	//	}
	//}
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

	pushObject(OBJ_BULDING, WINCX * 0.f, WINCY * -0.4f, 0);
	pushObject(OBJ_BULDING, WINCX * 0.35f, WINCY * -0.35f, 0);
	pushObject(OBJ_BULDING, WINCX * -0.35f, WINCY * -0.35f, 0);

	pushObject(OBJ_BULDING, WINCX * 0.f, WINCY * 0.4f, 1);
	pushObject(OBJ_BULDING, WINCX * 0.35f, WINCY * 0.35f, 1);
	pushObject(OBJ_BULDING, WINCX * -0.35f, WINCY * 0.35f, 1);
}
int CSceneMgr::Update(float fDeltaTime)
{
	if (false == m_bSummonAble)
	{
		m_fAccSummonTime += fDeltaTime;
		if (m_fAccSummonTime > CHARACTE_CREATE_TIME)
		{
			m_bSummonAble = true;
			m_fAccSummonTime = 0.f;
		}
	}	
	CreateEnemy(fDeltaTime);


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
	//CheckCollisionBuildingToArrow();
	CheckCollisionCharToBuilding();
	CheckCollisionCharToBullet();
	CheckCollisionCharToArrow();
	//Update(m_fNowTime - m_fStartTime);
	for (int i = 0; i < OBJ_END; ++i)
	{
		list<CObj*>::iterator iter = m_ObjList[i].begin();
		list<CObj*>::iterator iter_end = m_ObjList[i].end();
		for (; iter != iter_end; ++iter)
		{
			if (i != OBJ_BULDING)
			{
				pRenderer->DrawSolidRect((*iter)->GetObjInfo()->x,
					(*iter)->GetObjInfo()->y,
					(*iter)->GetObjInfo()->z,
					(*iter)->GetObjInfo()->size,
					(*iter)->GetObjInfo()->r,
					(*iter)->GetObjInfo()->g,
					(*iter)->GetObjInfo()->b,
					(*iter)->GetObjInfo()->a);
			}
			else
			{
				GLint imageNum = -1;
				(*iter)->GetTeamNum() == 0 ? imageNum = m_imageNum[IMAGE_BUILDING] : imageNum = m_imageNum[IMAGE_ENEMY_BUILDING];

				m_pRenderer->DrawTexturedRect((*iter)->GetObjInfo()->x,
					(*iter)->GetObjInfo()->y,
					(*iter)->GetObjInfo()->z,
					(*iter)->GetObjInfo()->size,
					(*iter)->GetObjInfo()->r,
					(*iter)->GetObjInfo()->g,
					(*iter)->GetObjInfo()->b,
					(*iter)->GetObjInfo()->a,
					imageNum);
			}
		}
	}
}
