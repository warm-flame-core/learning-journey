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

//向上调整法
void AdjustUp(HPDateType* a, int child);

//向下调整法
void AdjustDown(HPDateType* a, int size, int parent);

//判空
bool HeapEmpty(pHp Heap);

//堆排序
void HeapSort(HPDateType* a, int num);

//交换数据
void Swap(HPDateType* p1, HPDateType* p2);