#include "stdafx.h"
#include "CSceneMgr.h"


CSceneMgr::CSceneMgr()
{
}


CSceneMgr::~CSceneMgr()
{
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
		for (int j = 0; j < m_iObjCnt; ++j)
		{
			if (i == j) continue;
			
		}
	}
}
