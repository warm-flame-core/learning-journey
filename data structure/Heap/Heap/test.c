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

    // 开辟大小为 K 的数组作为堆的存储
    int* a = (int*)malloc(k * sizeof(int));
    if (a == NULL)
    {
        perror("malloc error");
        return;
    }

    const char* file = "date.txt";
    FILE* fout = fopen(file, "r"); // 以只读方式打开文件
    if (fout == NULL)
    {
        perror("file open error");
        return;
    }

    int x;

    // 取前 K 个数据建立初始堆
    for (int i = 0; i < k; i++)
    {
        fscanf(fout, "%d", &x);
        a[i] = x;
    }
    for (int i = (k - 2) / 2; i >= 0; i--)
    {
        AdjustDown(a, k, i);
    }
    // 此时数组 a 中有 k 个元素，将其调整为一个小根堆   
    while (fscanf(fout, "%d", &x) > 0)
    {
        // 拿新数据 x 和堆顶 a[0] 比较
        // 如果是求最大的 K 个数，且 x 比堆顶（当前 K 个里最小的）还大
        if (x > a[0])
        {
            a[0] = x;       // 替换堆顶
            AdjustDown(a, k, 0); // 向下调整，恢复小堆性质
        }
    }
    // 对这 K 个数进行堆排序
    int end = k - 1;
    while (end > 0)
    {
        Swap(&a[0], &a[end]); // 把堆顶（最小值）换到最后
        AdjustDown(a, end, 0); // 重新调整剩下的 end 个元素
        end--;
    }
    for (int i = 0; i < k; i++)
    {
        printf("%d ", a[i]);
    }

    fclose(fout);
    free(a);
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