#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

//初始化
void StackInit(pStack pk)
{
	assert(pk);
	pk->a = NULL;
	pk->top = 0;	//表示栈顶的下一个数据
	pk->capacity = 0;
}

//销毁
void StackDestroy(pStack pk)
{
	assert(pk);
	free(pk->a);
	pk->a = NULL;
	pk->top = pk->capacity = 0;
}

//压栈
void StackPush(pStack pk, STDateType x)
{
	assert(pk);
	if (pk->top == pk->capacity)
	{
		int newcapacity = pk->capacity == 0 ? 4 : pk->capacity * 2;
		STDateType* tmp = (STDateType*)realloc(pk->a, sizeof(STDateType) * newcapacity);
		if (tmp == NULL)
		{
			perror("StackPush realloc error");
			return;
		}
		pk->a = tmp;
		pk->capacity = newcapacity;
	}
	pk->a[pk->top] = x;
	pk->top++;
}

//出栈
void StackPop(pStack pk)
{
	assert(pk);
	assert(pk->top > 0);
	pk->top--;
}

//输出栈顶
STDateType StackTop(pStack pk)
{
	assert(pk);
	assert(pk->top > 0);
	return pk->a[pk->top - 1];
}

// 判空
bool StackEmpty(pStack pk)
{
	assert(pk);
	return pk->top == 0;
}

// 获取数据个数
int StackSize(pStack pk)
{
	assert(pk);
	return pk->top;
}