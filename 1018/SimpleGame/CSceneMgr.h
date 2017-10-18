#pragma once
#include "CObj.h"
#define MAX_OBJECTS_COUNT 10

class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

private:
	CObj*	m_ObjArray[MAX_OBJECTS_COUNT];
	int		m_iObjCnt{ 0 };

public:
	void	pushObject(CObj* pObject);
	void	CheckCollsion();

public:
	CObj**	GetObjArray() { return m_ObjArray; }
	int		GetObjCnt() { return m_iObjCnt; }

};

