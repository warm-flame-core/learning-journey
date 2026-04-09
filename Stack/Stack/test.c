#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

int main()
{
	Stack s1;
	StackInit(&s1);
	StackPush(&s1, 1);
	StackPush(&s1, 2);
	StackPush(&s1, 3);
	StackPush(&s1, 4);
	while (!StackEmpty(&s1))
	{
		printf("%d ", StackTop(&s1));
		StackPop(&s1);
	}
	StackDestroy(&s1);
	return 0;
}