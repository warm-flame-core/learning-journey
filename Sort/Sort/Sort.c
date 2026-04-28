#define _CRT_SECURE_NO_WARNINGS 1
#include "Sort.h"
#include "Stack.h"

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

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
		//内层循环，假设[0, emd]都已经是有序的,讲emd+1的值依次与有序的进行比较
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}

void ShellSort(int* a, int n)
{
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
					break;
			}
			a[end + gap] = tmp;
		}
	}
}

void BubbleSort(int* a, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int flag = 1;
		//已经有后面i个数字排好了，现在前面n-i个没排好，下边为[0, n-i-1]。那么j的取值就为[0, n-i-1-2]，即范围是[0, n-i-1)
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j + 1] < a[j])
			{
				flag = 0;
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
		if (flag)
			break;
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
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
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
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		end--;
	}
}


void SelectSort(int* a, int n)
{
	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int mid = begin;
		int max = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (a[mid] > a[i])
			{							// begin
				mid = i;				// 9 1 2 5 7 4 1 3
			}							// max  
			if (a[max] < a[i])			//	 min
			{
				max = i;
			}
		}
		Swap(&a[mid], &a[begin]);
		if (begin == max)
			max = mid;
		Swap(&a[max], &a[end]);
		begin++;
		end--;
	}
}

int Getmid(int* a, int left, int right)
{
	int mid = (left + right) / 2;
	if (a[left] < a[right])
	{
		if (a[mid] < a[left])
			return left;
		else if (a[left] < a[mid])
		{
			if (a[mid] < a[right])
				return mid;
			else
				return right;
		}
	}
	else//a[left] > a[right]
	{
		if (a[mid] < a[right])
			return right;
		else if (a[right] < a[mid])
		{
			if (a[mid] < a[left])
				return mid;
			else
				return left;
		}
	}
	return left;
}

//horare方法快排单趟
int QuickSortPast1(int* a, int left, int right)
{
	int mid = Getmid(a, left, right);	//三数取中，尽可能递归时满足像二叉树的性质
	Swap(&a[mid], &a[left]);
	int keyi = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && a[end] >= a[keyi])	//基准值在哪边，从基准值的另外一边开始移动
		{
			end--;
		}
		while (begin < end && a[begin] <= a[keyi])
		{
			begin++;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[keyi], &a[begin]);
	keyi = begin;
	return keyi;
}


//挖坑法快排单趟
int QuickSortPast2(int* a, int left, int right)
{
	int mid = Getmid(a, left, right);	//三数取中，尽可能递归时满足像二叉树的性质
	Swap(&a[mid], &a[left]);
	int keyi = left;
	int pit = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		while (begin < end && a[end] >= a[keyi])	//基准值在哪边，从基准值的另外一边开始移动
		{
			end--;
		}
		Swap(&a[pit], &a[end]);
		pit = end;
		while (begin < end && a[begin] <= a[keyi])
		{
			begin++;
		}
		pit = begin;
		Swap(&a[pit], &a[begin]);
	}
	Swap(&a[keyi], &a[begin]);
	keyi = begin;
}

//前后指针法快排单趟
int QuickSortPast3(int* a, int left, int right)
{
	int mid = Getmid(a, left, right);	//三数取中，尽可能递归时满足像二叉树的性质
	Swap(&a[mid], &a[left]);
	int keyi = left;
	int prev = left;
	int cur = prev + 1;
	while (cur <= right)
	{
		if (a[cur] < a[keyi] && ++prev != cur)
			Swap(&a[cur], &a[prev]);
		cur++;
	}
	Swap(&a[keyi], &a[prev]);
	return prev;
}

void QuickSort(int* a, int left, int right)
{
	if (left >= right)		//确保边界存在
		return;
	if (right - left + 1 < 10)	//小区间不用快排，减少递归
	{
		InsertSort(a + left, right - left + 1);
	}
	else
	{
		//int keyi = QuickSortPast1(a, left, right);
		//int keyi = QuickSortPast2(a, left, right);
		int keyi = QuickSortPast3(a, left, right);
		//[left,keyi - 1]	keyi	[keyi+1,right]
		QuickSort(a, left, keyi - 1);
		QuickSort(a, keyi + 1, right);
	}
}

void QuickSortNonR(int* a, int left, int right)
{
	Stack s1;
	StackInit(&s1);
	StackPush(&s1, right);
	StackPush(&s1, left);
	while (!StackEmpty(&s1))
	{
		int begin = StackTop(&s1);
		StackPop(&s1);
		int end = StackTop(&s1);
		StackPop(&s1);
		int keyi = QuickSortPast1(a, begin, end);
		//[begin, keyi - 1] keyi [ket + 1, end]
		if (keyi - 1 > begin)
		{
			StackPush(&s1, keyi - 1);
			StackPush(&s1, begin);
		}
		if (keyi + 1 < end)
		{
			StackPush(&s1, end);
			StackPush(&s1, keyi + 1);
		}
	}
	StackDestroy(&s1);
}

void _MergeSort(int* a, int* tmp, int left, int right)
{
	if (left >= right)
		return;
	int mid = (left + right) / 2;
	//[left, mid][mid + 1, right]
	_MergeSort(a, tmp, left, mid);
	_MergeSort(a, tmp, mid + 1, right);
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int win = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
			tmp[win++] = a[begin1++];
		else
			tmp[win++] = a[begin2++];
	}
	while (begin1 <= end1)
		tmp[win++] = a[begin1++];
	while (begin2 <= end2)
		tmp[win++] = a[begin2++];
	memcpy(a + left, tmp + left, sizeof(int) * (right - left + 1));
}

void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc fail");
		return;
	}
	_MergeSort(a, tmp, 0, n - 1);
	free(tmp);
}


void MergeSortNonR(int* a, int n)
{
	int gap = 0;
	for (gap = 2; gap < n; gap *= 2)
	{

	}
}