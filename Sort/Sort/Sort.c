#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"

void PrintfSort(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void InsertSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		//内层循环，假设[0, emd]都已经是有序的
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
			}
			else
			{
				break;
			}
			end--;
		}
		a[end + 1] = tmp;
	}
}



void BubbleSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		//已经有后面i个数字排好了，现在前面n-i个没排好，下边为[0, n-i-1]。那么j的取值就为[0, n-i-1-2]，即范围是[0, n-i-1)
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j + 1] < a[j])
			{
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}


//升序建立大堆
void AdjustDown(int* a, int n, int parent)
{
	int child = parent * 2 + 1;
	
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
			child++;
		if (a[parent] < a[child])
		{
			int tmp = a[parent];
			a[parent] = a[child];
			a[child] = tmp;
		}
		else
			break;
		parent = child;
		child = parent * +1;
	}

	
}
void HeapSort(int* a, int n)
{
	//建堆
	for (int i = (n - 1 - 1) / 2; i >= 0; i--)
	{
		AdjustDown(a, n, i);
	}
	int end = n - 1;
	//头和尾巴交换，让从头到尾的前一个进行向下调整，即每次把头已经是最大了，扔到尾巴后面就可以不管
	while (end > 0)
	{
		int tmp = a[0];
		a[0] = a[end];
		a[end] = tmp;
		AdjustDown(a, end, 0);
		end--;
	}
}