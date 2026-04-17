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

//交换数据
void Swap(HPDateType* p1, HPDateType* p2)
{
	*p1 = *p1 ^ *p2;
	*p2 = *p1 ^ *p2;
	*p1 = *p1 ^ *p2;
}

//向上调整
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

//向下调整法
void AdjustDown(HPDateType* a, int size, int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && a[child] > a[child + 1])
		{
			child++;
		}
		if (a[parent] > a[child])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//删除堆顶数据
void HeapPop(pHp Heap)
{
	assert(Heap);
	assert(Heap->a);
	Swap(&Heap->a[0], &Heap->a[Heap->size]);
	Heap->size--;
	AdjustDown(Heap->a, Heap->size, 0);
}

//判空
bool HeapEmpty(pHp Heap)
{
	return Heap->size == 0;
}

//堆排序
void HeapSort(HPDateType* a, int num)
{
	//降序建立大堆
	//升序建立小堆
	
	//从下往上建堆，向上调整法
	/*for (int i = 1; i <num; i++)
	{
		AdjustUp(a, i);
	}*/

	//从上往下建堆，向下调整法，但是子树必须满足堆的性质，直接从尾开始向下调整
	for (int i = (num - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, num, i);
	}


	//从上向下排序，先交换堆顶与末尾数据，讲次级数据参与排序，最小的数据排到最后
	int end = num - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}