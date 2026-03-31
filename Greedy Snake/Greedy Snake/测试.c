//#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
//#include <Windows.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <locale.h>
//void SetPos(short x, short y)
//{
//	COORD pos = { x, y };
//	HANDLE hOutput = NULL;
//	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleCursorPosition(hOutput, pos);
//}
//int main()
//{
//	system("mode con cols=100 lines=30");
//	system("title ̰贪吃蛇");
//	system("pause");
//	/*HANDLE hOutput = NULL;
//	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_CURSOR_INFO CursorInfo;
//	GetConsoleCursorInfo(hOutput, &CursorInfo);
//	CursorInfo.bVisible = false;
//	SetConsoleCursorInfo(hOutput, &CursorInfo); */
//	char* loc = NULL;
//	loc = setlocale(LC_ALL, NULL);
//	printf("%s\n", loc);
//	loc = setlocale(0, "");
//	printf("%s\n", loc);
//	printf("ab\n");
//	wchar_t ch1 = L'比';
//	wprintf(L"%lc\n", ch1);
//	SetPos(30, 20);
//	system("pause");
//	return 0;
//}