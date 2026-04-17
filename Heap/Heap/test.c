#define _CRT_SECURE_NO_WARNINGS 1
#include "Heap.h"
#include <time.h>

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

//void HeapTest03()
//{
//	int arr[] = { 5,4,8,1,55,44,88,33,12,5125,483,0,1,3,4,2 };
//	HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
//	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
//	{
//		printf("%d ", arr[i]);
//	}
//}


//随机弄一点数据
void CreateDate()
{
	srand((unsigned int)time(NULL));
	const char* file = "date.txt";
	FILE* pf = fopen(file, "w");
	if (pf == NULL)
	{
		perror("file open error");
		return;
	}
	int x = 0;
	for (int i = 0; i < 1000000; i++)
	{
		x = rand() % 1000001;
		fprintf(pf, "%d\n", x);
	}
	fclose(pf);
}

void HeapTest03()
{
	int k = 0;
	printf("请输入K：");
	scanf("%d", &k);
	printf("\n");
	int* a = (int*)malloc(k * sizeof(int));
	if (a == NULL)
	{
		perror("malloc error");
		return;
	}
	const char* file = "date.txt";
	FILE* fout = fopen(file, "r");
	if (fout == NULL)
	{
		perror("file open error");
		return;
	}
	int x;
	
	//取前K个数据建立堆
	for (int i = 0; i < k; i++)
	{
		fscanf(fout, "%d", &x);
		a[i] = x;
	}
	
	//剩下的数据依次比较堆顶，比堆顶更大的交换再向下调整
	while (fscanf(fout, "%d", &x) > 0)
	{
		a[0] = x;
		AdjustDown(a, k, 0);
	}
	
	//堆顶与堆尾调整，将最小的换到堆尾，再对剩下的堆排序
	int end = k - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}

	for (int i = 0; i < k; i++)
	{
		printf("%d ", a[i]);
	}
	fclose(fout);
}

int main()
{
	//HeapTest01();
	//HeapTest02();
	//HeapTest03();
	//CreateDate();
	
	HeapTest03();
	return 0;
}