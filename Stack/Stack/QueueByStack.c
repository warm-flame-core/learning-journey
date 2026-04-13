#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"
//用栈实现队列，对应LeetCode第232题

typedef struct {
    Stack s1;
    Stack s2;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* q = (MyQueue*)malloc(sizeof(MyQueue));
    StackInit(&q->s1);
    StackInit(&q->s2);
    return q;
}

void myQueuePush(MyQueue* obj, int x) {
    StackPush(&obj->s1, x);
}

int myQueuePop(MyQueue* obj) {
    if (StackEmpty(&obj->s2))
    {
        while (!StackEmpty(&obj->s1))
        {
            int tmp = StackTop(&obj->s1);
            StackPop(&obj->s1);
            StackPush(&obj->s2, tmp);
        }
    }

    int val = StackTop(&obj->s2);
    StackPop(&obj->s2);
    return val;
}

int myQueuePeek(MyQueue* obj) {
    if (StackEmpty(&obj->s2))
    {
        while (!StackEmpty(&obj->s1))
        {
            int tmp = StackTop(&obj->s1);
            StackPop(&obj->s1);
            StackPush(&obj->s2, tmp);
        }
    }
    return StackTop(&obj->s2);
}

bool myQueueEmpty(MyQueue* obj) {
    return StackEmpty(&obj->s1) && StackEmpty(&obj->s2);
}

void myQueueFree(MyQueue* obj) {
    StackDestroy(&obj->s1);
    StackDestroy(&obj->s2);
    free(obj);
    obj = NULL;
}