#define _CRT_SECURE_NO_WARNINGS 1
#include "Snake.h"

void Game()
{
	Snake snake = { 0 };
	GameStart(&snake);
}

int main()
{
	setlocale(LC_ALL, "");
	Game();
	return 0;
}