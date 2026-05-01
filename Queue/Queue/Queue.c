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

	/*入队列需要分情况讨论：
	如果队列为空（phead == NULL），新节点既是头也是尾
	如果队列不为空，将原队尾的 next 指向新节点，然后更新 ptail 指向新节点*/

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
	
	// 分情况讨论：
	// 1. 如果队列只有一个节点（phead->next == NULL），
	//    删除后队列变为空，需要同时置空 phead 和 ptail。
	// 2. 如果队列有多个节点，保存头节点，移动 phead 指针，然后释放旧头节点。

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