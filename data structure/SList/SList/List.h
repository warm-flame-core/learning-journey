#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int LTDateType;
typedef struct LTNode
{
	LTDateType date;
	struct LTNode* next;
	struct LTNode* prev;
}LTNode;

//双向链表的新增节点
LTNode* LTBuyNode(LTDateType x);

//双向链表的初始化
LTNode* LTInit();

//销毁
void LTDesTroy(LTNode* phead);

//打印
void LTPrint(LTNode* phead);

//尾插
void LTPushBack(LTNode* phead, LTDateType x);
//头插
void LTPushFront(LTNode* phead, LTDateType x);

//尾删
void LTPopBack(LTNode* phead);
//头删
void LTPopFront(LTNode* phead);


//在pos位置之后插入数据
void LTInsert(LTNode* pos, LTDateType x);
//删除pos节点
void LTErase(LTNode* pos);
LTNode* LTFind(LTNode* phead, LTDateType x);