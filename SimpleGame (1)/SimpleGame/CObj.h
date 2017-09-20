#pragma once

struct ObjInfo {
	float x; float y; float z;
	float size;
	float r; float g; float b; float a;
};
class CObj
{
public:
	CObj();
	CObj(float fX, float fY, float fZ, float fSize, float fR, float fG, float fB, float fA);
	~CObj();
public:
	ObjInfo*	GetObjInfo() { return &m_tObjInfo; }

private:
	ObjInfo m_tObjInfo;


};

