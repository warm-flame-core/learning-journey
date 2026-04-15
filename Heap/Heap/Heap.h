#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>


//堆的实现，使用小堆
typedef int HPDateType;

typedef struct HeapNode
{
	HPDateType* a;
	int size;
	int capacity;
}Hp,* pHp;

//初始化
void HeapInit(pHp Heap);

//销毁
void HeapDestroy(pHp Heap);

//进入堆
void HeapPush(pHp Heap, HPDateType x);

//取堆顶的数据
HPDateType HeapTop(pHp Heap);

//删除堆顶数据
void HeapPop(pHp Heap);

void AdjustUp(HPDateType* a, int child);

void HeapEmpty(pHp Heap);