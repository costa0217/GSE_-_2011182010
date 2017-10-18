#include "stdafx.h"
#include "CObjectMgr.h"


CObjectMgr::CObjectMgr()
{
	m_pSceneMgr = new CSceneMgr;

}


CObjectMgr::~CObjectMgr()
{
	list<CObj*>::iterator iter = m_ObjList.begin();
	list<CObj*>::iterator iter_end = m_ObjList.end();

	for (; iter != iter_end; ++iter)
	{
		delete (*iter);
		(*iter) = nullptr;
	}
	delete m_pSceneMgr;
}

void CObjectMgr::pushObject(CObj * pObject)
{
	//m_ObjList.emplace_back(pObject);
	m_pSceneMgr->pushObject(pObject);
}

void CObjectMgr::RenderObjects(Renderer * pRenderer)
{
	//list<CObj*>::iterator iter = m_ObjList.begin();
	//list<CObj*>::iterator iter_end = m_ObjList.end();

	//for (; iter != iter_end; ++iter)
	//{		
	//	(*iter)->Update(0.5f);
	//	pRenderer->DrawSolidRect((*iter)->GetObjInfo()->x,
	//								(*iter)->GetObjInfo()->y,
	//								(*iter)->GetObjInfo()->z,
	//								(*iter)->GetObjInfo()->size,
	//								(*iter)->GetObjInfo()->r,
	//								(*iter)->GetObjInfo()->g,
	//								(*iter)->GetObjInfo()->b,
	//								(*iter)->GetObjInfo()->a);
	//}
	CObj** pObjList = m_pSceneMgr->GetObjArray();
	int	iObjListCnt = m_pSceneMgr->GetObjCnt();
	for (int i = 0; i < iObjListCnt; ++i)
	{
		pObjList[i]->Update(0.5f);
		pRenderer->DrawSolidRect(pObjList[i]->GetObjInfo()->x,
								pObjList[i]->GetObjInfo()->y,
								pObjList[i]->GetObjInfo()->z,
								pObjList[i]->GetObjInfo()->size,
								pObjList[i]->GetObjInfo()->r,
								pObjList[i]->GetObjInfo()->g,
								pObjList[i]->GetObjInfo()->b,
								pObjList[i]->GetObjInfo()->a);
	}
}
