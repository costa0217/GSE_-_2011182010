#pragma once

#include "Renderer.h"

class CExBar
{
public:
	CExBar();
	~CExBar();
private:
	GLint	m_iExBarNum{ 0 };
	GLint	m_iExNum{ 0 };
	GLint	m_iExPointNum{ 0 };
	GLint	m_iNumImgNum{ 0 };

	float	m_fExPoint{ 0.f };

	int		m_iIcon[4];
	int		m_iIconCost[5];

private:
	float	m_fBurningTime{ 0.f };
	bool	m_bBurning{ false };


public:
	void GetImageNum(GLint exbar, GLint ex, GLint expoint, GLint numImg) {
		m_iExBarNum = exbar; m_iExNum = ex; m_iExPointNum = expoint; m_iNumImgNum = numImg;
	}
private:
	GLint	m_iWndButNum[5];
	GLint	m_iWndNum{ 0 };

	int		m_iPresentButtNum{ -1 };
public:
	void GetWndImgNum(GLint* arrWndBut, GLint wndNum) {
		memcpy(m_iWndButNum, arrWndBut, sizeof(GLint) * 5);
		m_iWndNum = wndNum;
	}
public:
	int	PushIcon(float fPosX, float fPosY);
	int ProcessIcon(int i);


public:
	int Update(float fTimeDelta);
	void Render(Renderer* pRenderer);
};

