#define _CRT_SECURE_NO_WARNINGS 1
#include "Snake.h"

int main()
{
	setlocale(LC_ALL, "");
	Snake snake = { 0 };
	GameStart(&snake);	//游戏初始化
	
	/*GameRun(&snake);
	GameEnd(&snake);*/
	return 0;
}