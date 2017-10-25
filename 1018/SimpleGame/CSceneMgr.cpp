#include "stdafx.h"
#include "CSceneMgr.h"


CSceneMgr::CSceneMgr()
{
	m_fStartTime = (float)timeGetTime() * 0.001f;   //√ ¥‹¿ß∑Œ πŸ≤„¡‹
}


CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < m_iObjCnt; ++i)
	{
		delete m_ObjArray[i];
		m_ObjArray[i] = nullptr;
	}
}

void CSceneMgr::pushObject(CObj * pObject)
{
	if (m_iObjCnt == MAX_OBJECTS_COUNT) return;

	m_ObjArray[m_iObjCnt] = pObject;
	++m_iObjCnt;
}

void CSceneMgr::CheckCollsion()
{
	for (int i = 0; i < m_iObjCnt; ++i)
	{
		for (int j = i; j < m_iObjCnt; ++j)
		{
			if (i == j) continue;

			ObjInfo* pRect1 = m_ObjArray[i]->GetObjInfo();
			ObjInfo* pRect2 = m_ObjArray[j]->GetObjInfo();

			if (pRect1->x - pRect1->size * 0.5f	< pRect2->x + pRect2->size * 0.5f &&
				pRect1->y - pRect1->size * 0.5f < pRect2->y + pRect2->size * 0.5f &&
				pRect1->x + pRect1->size * 0.5f > pRect2->x - pRect2->size * 0.5f &&
				pRect1->y + pRect1->size * 0.5f > pRect2->y - pRect2->size * 0.5f)
			{
				m_ObjArray[i]->SetCollision(true);
				m_ObjArray[j]->SetCollision(true);
			}
		}
	}
}
void CSceneMgr::RenderObjects(Renderer * pRenderer)
{
	m_fNowTime = (float)timeGetTime() * 0.001f;   //√ ¥‹¿ß∑Œ πŸ≤„¡‹

	CheckCollsion();
	for (int i = 0; i < m_iObjCnt; ++i)
	{
		m_ObjArray[i]->Update(m_fNowTime - m_fStartTime);
		pRenderer->DrawSolidRect(m_ObjArray[i]->GetObjInfo()->x,
			m_ObjArray[i]->GetObjInfo()->y,
			m_ObjArray[i]->GetObjInfo()->z,
			m_ObjArray[i]->GetObjInfo()->size,
			m_ObjArray[i]->GetObjInfo()->r,
			m_ObjArray[i]->GetObjInfo()->g,
			m_ObjArray[i]->GetObjInfo()->b,
			m_ObjArray[i]->GetObjInfo()->a);
	}

	m_fStartTime = m_fNowTime;
}
