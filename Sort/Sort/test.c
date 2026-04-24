#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

//void InsertSortTest()
//{
//	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
//	InsertSort(arr1, sizeof(arr1) / sizeof(int));
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}
//
//void BubbleSortTest()
//{
//	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
//	BubbleSort(arr1, sizeof(arr1) / sizeof(int));
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}
//
//void HeapSortTest()
//{
//	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
//	HeapSort(arr1, sizeof(arr1) / sizeof(int));
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}

//void ShellSortTest()
//{
//	int arr1[] = { 5,4,8,9,2,7,6,3,1,0 };
//	ShellSort(arr1, sizeof(arr1) / sizeof(int));
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}

//void SelectSortTest()
//{
//	int arr1[] = { 9,1,2,5,7,4,1,3 };
//	SelectSort(arr1, sizeof(arr1) / sizeof(int));
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}

//void QuickSortTest()
//{
//	int arr1[] = { 9,1,2,5,7,4,1,3 };
//	QuickSort(arr1, 0, sizeof(arr1) / sizeof(int) - 1);
//	PrintfSort(arr1, sizeof(arr1) / sizeof(int));
//}

void TestOP()
{
	srand(time(0));
	const int N = 10000000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand() + i;
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];
	}

	int begin1 = clock();
	//InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();

	int begin3 = clock();
	//SelectSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	HeapSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	QuickSort(a5, 0, N - 1);
	int end5 = clock();

	int begin6 = clock();
	//MergeSort(a6, N);
	int end6 = clock();

	int begin7 = clock();
	//BubbleSort(a7, N);
	int end7 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	printf("QuickSort:%d\n", end5 - begin5);
	printf("MergeSort:%d\n", end6 - begin6);
	printf("BubbleSort:%d\n", end7 - begin7);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
}

int main()
{
	/*printf("aaaaaaaa\n");
	InsertSortTest();
	BubbleSortTest();
	HeapSortTest();*/
	TestOP();
	//ShellSortTest();
	//SelectSortTest();
	//QuickSortTest();
	return 0;
}