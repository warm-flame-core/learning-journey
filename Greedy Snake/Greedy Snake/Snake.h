#pragma once
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
enum DIRECTION
{
	UP=1,
	DOWN,
	RIGHT,
	LEFT
};
enum GAME_STATUS
{
	NORMAL,
	KILL_WALL,
	KILL_SELF,
	ENDING
};
typedef struct SnakeNode
{
	int x;
	int y;
	struct SnakeNode* next;
}SnakeNode, * pSnakeNode;
typedef struct Snake
{
	pSnakeNode _pSnake;				//蛇头
	pSnakeNode _pFood;				//食物
	enum DIRECTION _Dir;			//方向
	enum GAME_STATUS _Status;		//游戏状态
	int _Socre;						//分数
	int _foodWeight;				//食物权重
	int _SleepTime;					//速度
}Snake, *pSnake;

//设置光标位置
void SetPos(short x, short y);

//游戏初始化
void GameStart(pSnake ps);

//欢迎信息
void WelcomeToGame();