#pragma once

#include "Renderer.h"

class CBomb
{
public:
	CBomb();
	~CBomb();
public:
	int Update(float fTimeDelta);
	void Render(Renderer* pRenderer);
};

