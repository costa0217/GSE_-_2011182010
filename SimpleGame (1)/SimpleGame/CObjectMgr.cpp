#include "stdafx.h"
#include "CObjectMgr.h"


CObjectMgr::CObjectMgr()
{
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
}

void CObjectMgr::pushObject( CObj * pObject)
{
	m_ObjList.emplace_back(pObject);
}

void CObjectMgr::RenderObjects(Renderer * pRenderer)
{
	list<CObj*>::iterator iter = m_ObjList.begin();
	list<CObj*>::iterator iter_end = m_ObjList.end();

	for (; iter != iter_end; ++iter)
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
}
