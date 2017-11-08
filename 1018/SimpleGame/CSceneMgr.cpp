#include "stdafx.h"
#include "CSceneMgr.h"


CSceneMgr::CSceneMgr()
{
	m_fStartTime = (float)timeGetTime() * 0.001f;   //√ ¥‹¿ß∑Œ πŸ≤„¡‹

	for (int i = 0; i < OBJ_END; ++i)
	{
		m_iObjCnt[i] = 0;
	}
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (int j = 0; j < m_iObjCnt[i]; ++j)
		{
			delete m_ObjArray[i][j];
			m_ObjArray[i][j] = nullptr;
		}
	}
}

void CSceneMgr::pushObject(OBJ_TYPE eType, CObj * pObject, int nObjNum)
{
	if (m_iObjCnt[eType] == MAX_OBJECTS_COUNT) return;


	m_ObjArray[eType][m_iObjCnt[eType]] = pObject;
	m_ObjArray[eType][m_iObjCnt[eType]]->SetSceneMgr(this);

	if (-1 != nObjNum)
	{
		m_ObjArray[eType][m_iObjCnt[eType]]->SetObjNum(nObjNum);
	}
	else
	{
		m_ObjArray[eType][m_iObjCnt[eType]]->SetObjNum(m_iObjCnt[eType]);
	}

	++m_iObjCnt[eType];
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
	for (int i = 0; i < m_iObjCnt[OBJ_BULDING]; ++i)
	{
		m_ObjArray[OBJ_BULDING][i]->SetColor(1.f, 1.f, 0.f);
		for (int j = 0; j < m_iObjCnt[OBJ_CHARACTER]; ++j)
		{
			ObjInfo* pBuilding	= m_ObjArray[OBJ_BULDING][i]->GetObjInfo();
			ObjInfo* pCharacter = m_ObjArray[OBJ_CHARACTER][j]->GetObjInfo();
			

			if (pBuilding->x - pBuilding->size * 0.5f	< pCharacter->x + pCharacter->size * 0.5f &&
				pBuilding->y - pBuilding->size * 0.5f	< pCharacter->y + pCharacter->size * 0.5f &&
				pBuilding->x + pBuilding->size * 0.5f	> pCharacter->x - pCharacter->size * 0.5f &&
				pBuilding->y + pBuilding->size * 0.5f	> pCharacter->y - pCharacter->size * 0.5f)
			{
				m_ObjArray[OBJ_BULDING][i]->SetLifePoint(m_ObjArray[OBJ_BULDING][i]->GetLifePoint() - m_ObjArray[OBJ_CHARACTER][j]->GetLifePoint());
				m_ObjArray[OBJ_BULDING][i]->SetColor(1.f, 0.f, 0.f);
				m_ObjArray[OBJ_CHARACTER][j]->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionCharToBullet()
{
	for (int i = 0; i < m_iObjCnt[OBJ_CHARACTER]; ++i)
	{
		m_ObjArray[OBJ_CHARACTER][i]->SetColor(1.f, 1.f, 1.f);
		for (int j = 0; j < m_iObjCnt[OBJ_BULLET]; ++j)
		{
			ObjInfo* pCharacter = m_ObjArray[OBJ_CHARACTER][i]->GetObjInfo();
			ObjInfo* pBullet = m_ObjArray[OBJ_BULLET][j]->GetObjInfo();
			///add

			if (pCharacter->x - pCharacter->size * 0.5f	< pBullet->x + pBullet->size * 0.5f &&
				pCharacter->y - pCharacter->size * 0.5f	< pBullet->y + pBullet->size * 0.5f &&
				pCharacter->x + pCharacter->size * 0.5f	> pBullet->x - pBullet->size * 0.5f &&
				pCharacter->y + pCharacter->size * 0.5f	> pBullet->y - pBullet->size * 0.5f)
			{
				m_ObjArray[OBJ_CHARACTER][i]->SetLifePoint(m_ObjArray[OBJ_CHARACTER][i]->GetLifePoint() - m_ObjArray[OBJ_BULLET][j]->GetLifePoint());
				m_ObjArray[OBJ_CHARACTER][i]->SetColor(1.f, 0.f, 0.f);
				m_ObjArray[OBJ_BULLET][j]->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::CheckCollisionBuildingToArrow()
{

	for (int i = 0; i < m_iObjCnt[OBJ_BULDING]; ++i)
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
	}
}
void CSceneMgr::CheckCollisionCharToArrow()
{
	for (int i = 0; i < m_iObjCnt[OBJ_CHARACTER]; ++i)
	{
		for (int j = 0; j < m_iObjCnt[OBJ_ARROW]; ++j)
		{
			if (m_ObjArray[OBJ_CHARACTER][i]->GetObjNum() == m_ObjArray[OBJ_ARROW][j]->GetObjNum()) continue;

			ObjInfo* pCharacter = m_ObjArray[OBJ_CHARACTER][i]->GetObjInfo();
			ObjInfo* pArrow = m_ObjArray[OBJ_ARROW][j]->GetObjInfo();


			if (pCharacter->x - pCharacter->size * 0.5f	< pArrow->x + pArrow->size * 0.5f &&
				pCharacter->y - pCharacter->size * 0.5f	< pArrow->y + pArrow->size * 0.5f &&
				pCharacter->x + pCharacter->size * 0.5f	> pArrow->x - pArrow->size * 0.5f &&
				pCharacter->y + pCharacter->size * 0.5f	> pArrow->y - pArrow->size * 0.5f)
			{
				m_ObjArray[OBJ_CHARACTER][i]->SetLifePoint(m_ObjArray[OBJ_CHARACTER][i]->GetLifePoint() - m_ObjArray[OBJ_ARROW][j]->GetLifePoint());
				m_ObjArray[OBJ_ARROW][j]->SetCollision(true);
			}
		}
	}
	
}
void CSceneMgr::Initialize()
{
	m_imageNum[OBJ_BULDING] = m_pRenderer->CreatePngTexture("./Textures/Building.png");
	m_imageNum[OBJ_CHARACTER] = m_pRenderer->CreatePngTexture("./Textures/Char.png");
	m_imageNum[OBJ_BULLET] = m_pRenderer->CreatePngTexture("./Textures/Bullet.png");
	m_imageNum[OBJ_ARROW] = m_pRenderer->CreatePngTexture("./Textures/Arrow.png");
}
void CSceneMgr::RenderObjects(Renderer * pRenderer)
{
	m_fNowTime = (float)timeGetTime() * 0.001f;   //√ ¥‹¿ß∑Œ πŸ≤„¡‹

	//CheckCollsion();
	CheckCollisionCharToBuilding();
	CheckCollisionCharToBullet();
	CheckCollisionBuildingToArrow();
	CheckCollisionCharToArrow();
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (int j = 0; j < m_iObjCnt[i]; )
		{
			if (1 == m_ObjArray[i][j]->Update(m_fNowTime - m_fStartTime))
			{
				delete m_ObjArray[i][j];
				m_ObjArray[i][j] = nullptr;

				for (int k = 0; k < m_iObjCnt[i] - j - 1; ++k)
				{
					m_ObjArray[i][j + k] = m_ObjArray[i][j + k + 1];
				}
				--m_iObjCnt[i];
			}
			else
			{
				++j;
			}
		}
	}

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (int j = 0; j < m_iObjCnt[i]; ++j)
		{
			/*pRenderer->DrawSolidRect(m_ObjArray[i][j]->GetObjInfo()->x,
				m_ObjArray[i][j]->GetObjInfo()->y,
				m_ObjArray[i][j]->GetObjInfo()->z,
				m_ObjArray[i][j]->GetObjInfo()->size,
				m_ObjArray[i][j]->GetObjInfo()->r,
				m_ObjArray[i][j]->GetObjInfo()->g,
				m_ObjArray[i][j]->GetObjInfo()->b,
				m_ObjArray[i][j]->GetObjInfo()->a);*/

			m_pRenderer->DrawTexturedRect(m_ObjArray[i][j]->GetObjInfo()->x,
				m_ObjArray[i][j]->GetObjInfo()->y,
				m_ObjArray[i][j]->GetObjInfo()->z,
				m_ObjArray[i][j]->GetObjInfo()->size,
				m_ObjArray[i][j]->GetObjInfo()->r,
				m_ObjArray[i][j]->GetObjInfo()->g,
				m_ObjArray[i][j]->GetObjInfo()->b,
				m_ObjArray[i][j]->GetObjInfo()->a,
				m_imageNum[i]);
		}
	}


	m_fStartTime = m_fNowTime;
}
