#define _CRT_SECURE_NO_WARNINGS 1
#include "Snake.h"
HANDLE hOutput = NULL;

void SetPos(short x, short y)
{
	COORD pos = { x, y };
	HANDLE hOutput = NULL;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void WelcomeToGame()
{
	SetPos(40, 15);
	printf("欢迎来到贪吃蛇游戏");
	SetPos(40, 25);//让按任意键继续的出现的位置好看点
	system("pause");
	system("cls");
	SetPos(25, 12);
	SetPos(25, 13);
	printf("⽤↑.↓.←.→分别控制蛇的移动，F3为加速，F4为减速\n");
	SetPos(25, 14);
	printf("加速将能得到更高的分数\n");
	SetPos(40, 25);
	system("pause");
	system("cls");
}

void CreateMap()
{
	int i = 0;
	SetPos(0, 0);
	for (i = 0; i < 57; i += 2)
	{
		wprintf(L"%lc", WALL);
	}
}

void GameStart(pSnake ps)
{
	system("mode con cols=100 lines=30");
	system("title ̰贪吃蛇");
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOutput, &CursorInfo); 
	WelcomeToGame();
	CreateMap();
	getchar();
}
