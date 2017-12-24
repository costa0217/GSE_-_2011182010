#pragma once

#include "Renderer.h"

class CLightning
{
public:
	CLightning();
	~CLightning();

public:
	float m_fPosX{ 0.f };
	float m_fPosY{ 0.f };

	bool	m_bAble{ false };
	float	m_fFrameTime{ 0.f };
	int		m_iAnimCnt{ 0 };

	GLint	m_iImage;

public:
	int Update(float fTimeDelta);
	void Render(Renderer* pRenderer);
};

