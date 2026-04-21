#define _CRT_SECURE_NO_WARNINGS 1
#include "Queue.h"
//队列的初始化和销毁
void QueueInit(pQueue pq)
{
	assert(pq);
	pq->phead = pq->ptail = NULL;
	pq->size = 0;
}
void QueueDestroy(pQueue pq)
{
	assert(pq);
	pQNode pcur = pq->phead;
	while (pcur)
	{
		pQNode next = pcur->next;
		free(pcur);
		pcur = next;
	}
	pq->phead = pq->ptail = NULL;
	pq->size = 0;
}

//入队列
void QueuePush(pQueue pq, QDateType x)
{
	pQNode newnode = (pQNode)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc newnode error");
		return;
	}
	newnode->val = x;
	newnode->next = NULL;
	if (pq->phead == NULL)
	{
		pq->phead = pq->ptail = newnode;

	}
	else
	{
		pq->ptail->next = newnode;
		pq->ptail = newnode;
	}
	pq->size++;
}

//出队列
void QueuePop(pQueue pq)
{
	assert(pq);
	assert(pq->phead);
	
	if (pq->phead->next == NULL)
	{
		free(pq->phead);
		pq->phead = pq->ptail = NULL;
	}
	else
	{
		pQNode del = pq->phead;
		pq->phead = pq->phead->next;
		free(del);
		del = NULL;
	}
	pq->size--;
}

//取队头数据
QDateType QueueFront(pQueue pq)
{
	assert(pq);
	assert(pq->phead);

	return pq->phead->val;
}

//取队尾数据
QDateType QueneBack(pQueue pq)
{
	assert(pq);
	assert(pq->ptail);

	return pq->ptail->val;
}

//队列有几个数据
int QueneSize(pQueue pq)
{
	assert(pq);

	return pq->size;
}

//判空
bool QueneEmpty(pQueue pq)
{
	assert(pq);

	return pq->size == 0;
}