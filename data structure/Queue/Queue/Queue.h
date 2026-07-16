#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef int QDateType;

typedef struct QueueNode	//结构体定义节点
{
	QDateType val;
	struct QueueNode* next;
}QNode, * pQNode;

typedef struct Queue	//结构体定义头尾指针和节点个数
{
	pQNode ptail;
	pQNode phead;
	int size;
}Queue, * pQueue;


void QueueInit(pQueue pq);
void QueueDestroy(pQueue pq);

void QueuePush(pQueue pq, QDateType x);

void QueuePop(pQueue pq);

QDateType QueueFront(pQueue pq);

QDateType QueneBack(pQueue pq);

int QueneSize(pQueue pq);

bool QueneEmpty(pQueue pq);