#pragma once
#include "Renderer.h"

#include "CObj.h"

class CObjectMgr
{
public:
	CObjectMgr();
	~CObjectMgr();

private:
	list<CObj*>		m_ObjList;

public:
	list<CObj*>*	GetObjectList() { return &m_ObjList; };

public:
	void pushObject(CObj* pObject);

	void RenderObjects(Renderer* pRenderer);
};

