#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"

//void HeapTest01()
//{
//	Hp p1;
//	HeapInit(&p1);
//	HeapPush(&p1, 5);
//	HeapPush(&p1, 1);
//	HeapPush(&p1, 7);
//	HeapPush(&p1, 2);
//	HeapPush(&p1, 9);
//	HeapPop(&p1);
//}

//void HeapTest02()
//{
//	int arr[] = { 5,4,8,1,55,44,88,33,12,5125,483,0,1,3,4,2 };
//	Hp p2;
//	HeapInit(&p2);
//	int i = 0;
// 	for (i = 0; i < (sizeof(arr) / sizeof(int)); i++)
//	{
//		HeapPush(&p2, arr[i]);
//	}
//}

void HeapTest03()
{
	int arr[] = { 5,4,8,1,55,44,88,33,12,5125,483,0,1,3,4,2 };
	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		printf("%d ", arr[i]);
	}
}


int main()
{
	//HeapTest01();
	//HeapTest02();

	HeapTest03();
	return 0;
}