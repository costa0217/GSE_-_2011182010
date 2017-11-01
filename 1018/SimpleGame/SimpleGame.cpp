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

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

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
		//(rand()%254+ 1)/255.f
		g_SceneManager->pushObject(OBJ_CHARACTER, new CCharacter(0, x - 500 * 0.5f, 500 * 0.5f - y, 0));
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

	//g_ObjManager->pushObject(new CObj(100, 100, 0, 2, 1, 0, 0, 1));
	//g_ObjManager->pushObject(new CObj(100, -100, 0, 4, 1, 1, 0, 1));
	//g_ObjManager->pushObject(new CObj(-100, -100, 0, 6, 1, 1, 1, 1));
	g_SceneManager->pushObject(OBJ_BULDING, new CBuilding(1, 0, 0, 0));

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete g_SceneManager;

    return 0;
}

