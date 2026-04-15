#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

void HeapTest01()
{
	Hp p1;
	HeapInit(&p1);
	HeapPush(&p1, 5);
	HeapPush(&p1, 1);
	HeapPush(&p1, 7);
	HeapPush(&p1, 2);
	HeapPush(&p1, 9);
}

int main()
{
	HeapTest01();
	return 0;
}