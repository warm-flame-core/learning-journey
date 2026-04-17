#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
typedef int STDateType;
typedef struct Stack
{
	STDateType* a;
	int top;	//表示栈顶元素的下一个
	int capacity;
}Stack,* pStack;

//初始化
void StackInit(pStack pk);

//销毁
void StackDestroy(pStack pk);

//压栈
void StackPush(pStack pk, STDateType x);

//出栈
void StackPop(pStack pk);

//输出栈顶
STDateType StackTop(pStack pk);

// 判空
bool StackEmpty(pStack pk);

// 获取数据个数
int StackSize(pStack pk);