#pragma once
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define KEY_PRESS(vk)  ((GetAsyncKeyState(vk)&1)?1:0)

#define WALL L'■'
#define BODY L'●'
#define FOOD L'★'
#define POS_X 6
#define POS_Y 20
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

//初始化地图
void CreateMap();

//初始化蛇
void InitSnake(pSnake ps);

//创造食物
void CreateFood(pSnake ps);

//运行游戏
void GameRun(pSnake ps);

//蛇走一步
void SnakeMove(pSnake ps);

//下一步是不是食物
int NextIsFood(pSnakeNode pnext, pSnake ps);

//吃掉食物
void EatFood(pSnakeNode pnext, pSnake ps);

//下一步不是食物
void NotEatFood(pSnakeNode pnext, pSnake ps);

//撞墙了
void KillByWall(pSnake ps);

//撞到自己了
void KillBySelf(pSnake ps);

//游戏结束
void GameOver(pSnake ps);