#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
//#include "BinaryTree.h"

struct BinaryTree;	//Ç°ÖÃÉùÃ÷

typedef struct BinaryTree* QDateType;

typedef struct QueueNode
{
	QDateType val;
	struct QueueNode* next;
}QNode, * pQNode;

typedef struct Queue
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