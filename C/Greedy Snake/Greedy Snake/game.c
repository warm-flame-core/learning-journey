#define _CRT_SECURE_NO_WARNINGS 1
#include "Snake.h"

void Game()
{
	char ch = 0;
	do
	{
		Snake snake = { 0 };
		GameStart(&snake);
		GameRun(&snake);
		GameOver(&snake);
		SetPos(26, 10);
		printf("再来一局吗?(Y/N):");
		ch = getchar();
		while (getchar() != '\n');
	} while (ch == 'Y' || ch == 'y');
}

int main()
{
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "");
	Game();
	return 0;
}