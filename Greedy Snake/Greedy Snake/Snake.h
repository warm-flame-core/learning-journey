#pragma once
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#define WALL L'□'
#define BODY L'●'
#define FOOD L'★'
extern HANDLE hOutput;
enum DIRECTION
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};
enum GAME_STATUS
{
	NORMAL,
	KILL_WALL,
	KILL_SELF,
	ENDING
};

//蛇的节点，单链表的形式
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;

//维护整个游戏有关的信息，蛇头、食物，蛇头方向、游戏状态、当前分数、食物权重、游戏速度
typedef struct Snake
{
	pSnakeNode _pSnake;
	pSnakeNode _pFood;
	enum DIRECTION _Dir;
	enum GAME_STATUS _Status;
	int _sorce;
	int _FoodWeight;
	int _Speed;
}Snake,* pSnake;

//定位坐标
void SetPos(short x, short y);

//初始化游戏
void GameStart(pSnake ps);

//打印欢迎界面
void WelcomeToGame();

//初始化棋盘
void CreateMap();
