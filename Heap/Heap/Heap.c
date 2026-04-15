#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

//初始化
void HeapInit(pHp Heap)
{
	assert(Heap);
	Heap->a = NULL;
	Heap->capacity = Heap->size = 0;
}

//销毁
void HeapDestroy(pHp Heap)
{
	assert(Heap);
	free(Heap->a);
	Heap->a = NULL;
	Heap->capacity = Heap->size = 0;
}

void Swap(HPDateType* p1, HPDateType* p2)
{
	*p1 = *p1 ^ *p2;
	*p2 = *p1 ^ *p2;
	*p1 = *p1 ^ *p2;
}

void AdjustUp(HPDateType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[parent], &a[child]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

//进入堆
void HeapPush(pHp Heap, HPDateType x)
{
	assert(Heap);
	if (Heap->size == Heap->capacity)
	{
		int newcapacity = Heap->capacity == 0 ? 4 : Heap->capacity * 2;
		HPDateType* tmp = (HPDateType*)realloc(Heap->a, sizeof(HPDateType) * newcapacity);
		if (tmp == NULL)
		{
			perror("StackPush realloc error");
			return;
		}
		Heap->a = tmp;
		Heap->capacity = newcapacity;
	}
	Heap->a[Heap->size] = x;
	Heap->size++;
	AdjustUp(Heap->a, Heap->size - 1);
}

//取堆顶的数据
HPDateType HeapTop(pHp Heap)
{
	assert(Heap);
	assert(Heap->a);
	return Heap->a[0];
}

void AdjustDown(HPDateType* a, int size, int parent)
{

}

//删除堆顶数据
void HeapPop(pHp Heap)
{
	assert(Heap);
	assert(Heap->a);
	Swap(&Heap->a[0], &Heap->a[Heap->size]);
	Heap->size--;
	
}

bool HeapEmpty(pHp Heap)
{
	return Heap->size == 0;
}