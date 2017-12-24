#include "stdafx.h"
#include "CExBar.h"


CExBar::CExBar()
{
	for (int i = 0; i < 4; ++i)
	{
		m_iIcon[i] = rand() % 5;
	}
	m_iIconCost[0] = 5;
	m_iIconCost[1] = 5;
	m_iIconCost[2] = 3;
	m_iIconCost[3] = 3;
	m_iIconCost[4] = 6;
}


CExBar::~CExBar()
{
}

int CExBar::PushIcon(float fPosX, float fPosY)
{
	for (int i = 0; i < 4; ++i)
	{
		if (-210.f + 50.f + 60 * i - 50.f * 0.5f	< fPosX &&
				-350.f - 50.f * 0.5f	< fPosY &&
				-210.f + 50.f + 60 * i + 50.f * 0.5f	> fPosX &&
				-350.f + 50.f * 0.5f	> fPosY)
		{
			if (m_iIconCost[m_iIcon[i]] < m_fExPoint)
			{
				if (m_iIcon[i] == 4)	// น๖วม
				{
					ProcessIcon(i);
					m_bBurning = true;
					return -1;
				}
			
				return m_iIcon[i];
			}
		}
	}
	return -1;
}

int CExBar::ProcessIcon(int i)
{
	m_fExPoint -= float(m_iIconCost[i]);
	m_iIcon[i] = rand() % 5;
	if (i == 4)
	{
		
	}
	return 0;
}

int CExBar::Update(float fTimeDelta)
{
	float fBurnRate = 1.f;

	if (m_bBurning)
	{
		m_fBurningTime += fTimeDelta;
		fBurnRate = 2.f;
		if (m_fBurningTime > 2.f)
		{
			m_fBurningTime = 0.f;
			m_bBurning = false;
		}
	}


	m_fExPoint += 5 * fTimeDelta * fBurnRate;
	if (m_fExPoint > 10.f)
	{
		m_fExPoint = 10.f;
	}


	return 0;
}

void CExBar::Render(Renderer * pRenderer)
{
	// expoint
	float r = 1.f;
	float g = 1.f;
	float b = 1.f;
	if (m_bBurning)
	{
		g = 0.f;
		b = 0.f;
	}

	pRenderer->DrawTexturedRectXY((WINCX * 0.8f * -0.5f) + m_fExPoint * 0.1f * (WINCX * 0.8f) * 0.5f, -295.f, 1.f,
		m_fExPoint * 0.1f * (WINCX * 0.8f), 30.f,
		r, g, b, 1.f,
		m_iExPointNum,
		0.001f);
	// exbar
	{
	pRenderer->DrawTexturedRectXY(180.f, -295.f, 1.f,	40.f, 30.f,	1.f, 1.f, 1.f,0.8f,m_iExBarNum,0.0005f);
	pRenderer->DrawTexturedRectXY(140.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f,m_iExBarNum,0.0005f);
	pRenderer->DrawTexturedRectXY(100.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f,m_iExBarNum,0.0005f);
	pRenderer->DrawTexturedRectXY(60.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f,m_iExBarNum,0.0005f);
	pRenderer->DrawTexturedRectXY(20.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	pRenderer->DrawTexturedRectXY(-20.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	pRenderer->DrawTexturedRectXY(-60.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	pRenderer->DrawTexturedRectXY(-100.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	pRenderer->DrawTexturedRectXY(-140.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	pRenderer->DrawTexturedRectXY(-180.f, -295.f, 1.f, 40.f, 30.f,	1.f, 1.f, 1.f, 0.8f, m_iExBarNum, 0.0005f);
	}
	// ex
	pRenderer->DrawTexturedRectXY(118.f, -350.f, 1.f, 95.f*0.3f, 118.f*0.3f,1.f, 1.f, 1.f, 1.f,	m_iExNum,0.0005f);	
	// exnum
	pRenderer->DrawTexturedRectSeqXY(160.f, -347.f, 1.f,50.f, 60.f ,1.f, 1.f, 1.f, 1.f,m_iNumImgNum, 1.f, int(m_fExPoint),1, 11,0.0005f);


	pRenderer->DrawTexturedRectXY(-70.f, -340.f, 1.f,
		280.f, 70.f,
		1.f, 1.f, 1.f, 1.f,
		m_iWndNum,
		0.001f);

	for (int i = 0; i < 4; ++i)
	{
		pRenderer->DrawTexturedRectXY(-210.f + 50.f + 60 * i, -350.f, 1.f,
			50.f, 50.f,
			1.f, 1.f, 1.f, 1.f,
			m_iWndButNum[m_iIcon[i]],
			0.001f);

		pRenderer->DrawTexturedRectSeqXY(-210.f + 50.f + 60 * i + 10, -350.f - 10, 1.f,
			20.f, 30.f, 1.f, 1.f, 1.f, 1.f, m_iNumImgNum, 1.f, m_iIconCost[m_iIcon[i]], 1, 11, 0.0005f);
	}

}
