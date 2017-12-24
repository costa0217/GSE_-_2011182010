#include "stdafx.h"
#include "CLightning.h"


CLightning::CLightning()
{
}


CLightning::~CLightning()
{
}

int CLightning::Update(float fTimeDelta)
{
	if (m_bAble)
	{
		m_fFrameTime += fTimeDelta;
		if (m_fFrameTime > 0.05f)
		{
			m_fFrameTime = 0.f;
			++m_iAnimCnt;
			int nMaxCnt = 10;
			if (m_iAnimCnt > nMaxCnt)
			{
				m_bAble = false;
				m_iAnimCnt = 0;
			}
		}
	}


	return 0;
}

void CLightning::Render(Renderer * pRenderer)
{
	if (m_bAble)
	{
		pRenderer->DrawTexturedRectSeqXY(m_fPosX, m_fPosY + 650.f * 0.4f * 0.5f, 1.f,
			140.f * 0.4f , 650.f * 0.4f,
			1.f, 1.f, 1.f, 1.f, m_iImage,
			m_iAnimCnt, 0, 10, 1, 0.9f);
	}
}
