#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

void InsertSortTest()
{
	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
	InsertSort(arr1, sizeof(arr1) / sizeof(int));
	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
}

void BubbleSortTest()
{
	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
	BubbleSort(arr1, sizeof(arr1) / sizeof(int));
	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
}

void HeapSortTest()
{
	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
	HeapSort(arr1, sizeof(arr1) / sizeof(int));
	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
}

int main()
{
	printf("aaaaaaaa\n");
	InsertSortTest();
	BubbleSortTest();
	HeapSortTest();
	return 0;
}