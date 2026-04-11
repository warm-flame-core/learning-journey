#define _CRT_SECURE_NO_WARNINGS 1
#include "Queue.h"

int main()
{
	Queue q1;
	QueueInit(&q1);
	QueuePush(&q1, 1);
	QueuePush(&q1, 2);
	QueuePush(&q1, 3);
	QueuePush(&q1, 4);
	while (!QueneEmpty(&q1))
	{
		printf("%d ", QueneFront(&q1));
		QuenePop(&q1);
	}
	printf("\n");
	return 0;
}