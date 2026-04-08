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
	printf("用上，下，左，右分别控制蛇的移动，Z为加速，左边ctrl为减速\n");
	printf("加速将能得到更高的分数。\n");
	SetPos(40, 25);
	system("pause");
	system("cls");
	SetPos(60, 15);
}

void CreateMap()
{
	int i = 0;
	SetPos(0, 0);
	for (i = 0; i < 58; i += 2)
	{
		wprintf(L"%c", WALL);
	}
	SetPos(0, 26);
	for (i = 0; i < 58; i += 2)
	{
		wprintf(L"%c", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(0, i);
		wprintf(L"%c", WALL);
	}
	for (i = 1; i < 26; i++)
	{
		SetPos(56, i);
		wprintf(L"%c", WALL);
	}
}

void InitSnake(pSnake ps)
{
	pSnakeNode pcur = NULL;
	//头插法
	for (int i = 0; i < 5; i++)
	{
		pcur = (pSnakeNode)malloc(sizeof(SnakeNode));
		if (pcur == NULL)
		{
			perror("InitSnake malloc error");
			exit(1);
		}
		pcur->next = NULL;
		pcur->x = POS_X + i * 2;
		pcur->y = POS_Y;
		if (ps->_pSnake == NULL)
		{
			ps->_pSnake = pcur;
		}
		else
		{
			pcur->next = ps->_pSnake;
			ps->_pSnake = pcur;
		}
	}
	pcur = ps->_pSnake;
	while (pcur)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%c", BODY);
		pcur = pcur->next;
	}
	ps->_Dir = RIGHT;
	ps->_foodWeight = 10;
	ps->_SleepTime = 200;
	ps->_Socre = 0;
	ps->_Status = NORMAL;
}

void CreateFood(pSnake ps)
{
	int x = 0;
	int y = 0;
	again:
	do
	{
		x = rand() % 52 + 2;
		y = rand() % 25 + 1;
	} while (x % 2 != 0);
	pSnakeNode pcur = ps->_pSnake;
	while (pcur)
	{
		if (pcur->x == x && pcur->y == y)
		{
			goto again;
		}
		pcur = pcur->next;
	}
	pSnakeNode pfood = (pSnakeNode)malloc(sizeof(SnakeNode));
	if (pfood == NULL)
	{
		perror("CreateFood malloc error");
		exit(1);
	}
	else 
	{
		pfood->x = x;
		pfood->y = y;
	}
	SetPos(pfood->x, pfood->y);
	wprintf(L"%c", FOOD);
	pfood->next = pfood;
	ps->_pFood = pfood;
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
	CreateMap();

	InitSnake(ps);

	CreateFood(ps);

}

void PrintHelp()
{
	SetPos(64, 14);
	wprintf(L"%ls", L"不能穿墙，不能咬到自己");
	SetPos(64, 15);
	wprintf(L"%ls", L"用 ↑. ↓ . ← . → 来控制蛇的移动");
	SetPos(64, 16);
	wprintf(L"%ls", L"按Z加速，左边ctrl减速");
	SetPos(64, 17);
	wprintf(L"%ls", L"按ESC退出游戏，按空格暂停游戏");
}

void StopGame()
{
	while (1)
	{
		Sleep(200);
		if (KEY_PRESS(VK_SPACE))
			break;
	}
}

int NextIsFood(pSnakeNode pnext, pSnake ps)
{
	return (pnext->x == ps->_pFood->x && pnext->y == ps->_pFood->y);
}

void EatFood(pSnakeNode pnext, pSnake ps)
{
	ps->_pFood->next = ps->_pSnake;
	ps->_pSnake = ps->_pFood;
	free(pnext);
	pnext = NULL;
	pSnakeNode pcur = ps->_pSnake;
	while (pcur)
	{
		SetPos(pcur->x, pcur->y);
		wprintf(L"%c", BODY);
		pcur = pcur->next;
	}
	CreateFood(ps);
}

void NotEatFood(pSnakeNode pn, pSnake ps)
{
	pn->next = ps->_pSnake;
	ps->_pSnake = pn;

	pSnakeNode cur = ps->_pSnake;
	while (cur->next != NULL && cur->next->next != NULL)
	{
		SetPos(cur->x, cur->y);
		wprintf(L"%lc", BODY);
		cur = cur->next;
	}

	//把最后一个结点打印成空格
	SetPos(cur->next->x, cur->next->y);
	printf("  ");

	//释放最后一个结点
	free(cur->next);

	//把倒数第二个节点的地址置为NULL
	cur->next = NULL;
}

void KillByWall(pSnake ps)
{
	if (ps->_pSnake->x == 0 || ps->_pSnake->x == 56 ||
		ps->_pSnake->y == 0 || ps->_pSnake->y == 26)
		ps->_Status = KILL_WALL;
}

void KillBySelf(pSnake ps)
{
	pSnakeNode pcur = ps->_pSnake->next;
	while (pcur)
	{
		if (ps->_pSnake->x == pcur->x && ps->_pSnake->y == pcur->y)
		{
			ps->_Status = KILL_SELF;
			break;
		}
		pcur = pcur->next;
	}
}

void SnakeMove(pSnake ps)
{
	pSnakeNode pnext = (pSnakeNode)malloc(sizeof(SnakeNode));
	switch (ps->_Dir)
	{
	case UP:
		pnext->x = ps->_pSnake->x;
		pnext->y = ps->_pSnake->y - 1;
		break;
	case DOWN:
		pnext->x = ps->_pSnake->x;
		pnext->y = ps->_pSnake->y + 1;
		break;
	case RIGHT:
		pnext->x = ps->_pSnake->x + 2;
		pnext->y = ps->_pSnake->y;
		break;
	case LEFT:
		pnext->x = ps->_pSnake->x - 2;
		pnext->y = ps->_pSnake->y;
		break;
	}
	if (NextIsFood(pnext, ps))
		EatFood(pnext, ps);
	else
		NotEatFood(pnext, ps);
	KillByWall(ps);
	KillBySelf(ps);
}

void GameRun(pSnake ps)
{
	PrintHelp();
	do
	{
		SetPos(64, 10);
		printf("当前分数：%2d", ps->_Socre);
		SetPos(64, 11);
		printf("当前食物的权重：%2d", ps->_foodWeight);
		if (KEY_PRESS(VK_UP) && ps->_Dir != DOWN)
		{
			ps->_Dir = UP;
		}
		else if (KEY_PRESS(VK_DOWN) && ps->_Dir != UP)
		{
			ps->_Dir = DOWN;
		}
		else if (KEY_PRESS(VK_LEFT) && ps->_Dir != RIGHT)
		{
			ps->_Dir = LEFT;
		}
		else if (KEY_PRESS(VK_RIGHT) && ps->_Dir != LEFT)
		{
			ps->_Dir = RIGHT;
		}
		else if (KEY_PRESS(VK_ESCAPE))
		{
			ps->_Status = ENDING;
		}
		else if (KEY_PRESS(VK_LCONTROL))
		{
			//减速
			if (ps->_foodWeight > 2)
			{
				ps->_SleepTime += 30;
				ps->_foodWeight -= 2;
			}
		}
		else if (KEY_PRESS(0x5A))
		{
			//加速
			if (ps->_SleepTime > 80)
			{
				ps->_SleepTime -= 30;
				ps->_foodWeight += 2;
			}
		}
		else if (KEY_PRESS(VK_SPACE))
		{
			StopGame();
		}

		SnakeMove(ps);
		Sleep(ps->_SleepTime);
	} while (ps->_Status == NORMAL);
}

void GameOver(pSnake ps)
{
	SetPos(25, 9);
	if (ps->_Status == KILL_WALL)
		wprintf(L"撞墙了");
	else if (ps->_Status == KILL_SELF)
		wprintf(L"吃到自己了");
	else if (ps->_Status == ENDING)
		wprintf(L"退出了");
	pSnakeNode pcur = ps->_pSnake;
	while (pcur)
	{
		pSnakeNode del = pcur;
		pcur = pcur->next;
		free(del);
	}
	ps->_pSnake = NULL;
}