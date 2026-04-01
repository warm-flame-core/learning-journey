#define _CRT_SECURE_NO_WARNINGS 1
#include "Snake.h"
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
	SetPos(40, 25);
	system("pause");
	system("cls");
	SetPos(25, 12);
	SetPos(25, 13);
	printf("用上，下，左，右分别控制蛇的移动，F3为加速，F4为减速\n");
	printf("加速将能得到更高的分数。\n");
	SetPos(40, 25);
	system("pause");
	system("cls");
}

void GameStart(pSnake ps)
{
	system("mode con cols=100 lines=30");
	system("title 贪吃蛇");
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hOutput, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(hOutput, &CursorInfo);
	WelcomeToGame();
	/*CreateMap();
	InitSnake(ps);
	CreateFood(ps);*/
	getchar();
}
