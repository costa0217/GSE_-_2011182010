/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "CSceneMgr.h"
#include "CCharacter.h"
#include "CBuilding.h"

Renderer *g_Renderer = NULL;
CSceneMgr*	g_SceneManager = NULL;

DWORD dwTime = 0;
DWORD dwPreTime = 0;
float fTime = 33.f;	//한프레임 시간(밀리세컨드 1초 = 1000밀리초)

GLvoid MousePosition(int x, int y);
void RenderScene(void)
{
	float fDivide = 1 / 255.f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(181 * fDivide, 214 * fDivide, 146 * fDivide, 1.0f);

	// Renderer Test
	g_SceneManager->RenderObjects(g_Renderer);

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		g_SceneManager->CreateCharacter(x - WINCX * 0.5f, WINCY * 0.5f - y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		g_SceneManager->m_bClick = false;
	}

}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}
GLvoid TimerFunction(int value)
{
	// 메인프레임 업데이트 구문
	dwTime = timeGetTime() * 0.001f;
	if (-1 == g_SceneManager->Update(fTime * 0.001f))
	//if (-1 == g_SceneManager->Update(float(dwTime - dwPreTime)))
		delete g_SceneManager;

	glutTimerFunc(fTime, TimerFunction, 1); // 타이머 함수 설정 
	glutPostRedisplay();

	dwPreTime = dwTime;
}
GLvoid	MousePosition(int x, int y)
{
	g_SceneManager->m_fMouseX = x - WINCX * 0.5f;
	g_SceneManager->m_fMouseY = WINCY * 0.5f - y;
}
int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINCX, WINCY);
	glutCreateWindow("Game Software Engineering KPU");

	srand((unsigned int)time(NULL));


	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(WINCX, WINCY);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	g_SceneManager = new CSceneMgr();
	g_SceneManager->SetRenderer(g_Renderer);
	g_SceneManager->Initialize();


	//g_SceneManager->pushObject(OBJ_BULDING, new CBuilding(1, 150, -300, 0));
	//g_SceneManager->pushObject(OBJ_BULDING, new CBuilding(1, 0, -320, 0));
	//g_SceneManager->pushObject(OBJ_BULDING, new CBuilding(1, -150, -300, 0));

	glutDisplayFunc(RenderScene);
	glutTimerFunc(fTime, TimerFunction, 1); // 타이머 함수 설정 

	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutPassiveMotionFunc(MousePosition);
	glutMotionFunc(MousePosition);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete g_SceneManager;

    return 0;
}

