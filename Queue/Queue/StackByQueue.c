#define _CRT_SECURE_NO_WARNINGS 1
#include "Queue.h"


//用队列模拟栈，对应leetcode第225题
typedef struct {
    Queue q1;
    Queue q2;
} MyStack;


MyStack* myStackCreate() {
    MyStack* pst = (MyStack*)malloc(sizeof(MyStack));
    QueueInit(&pst->q1);
    QueueInit(&pst->q2);
    return pst;
}

void myStackPush(MyStack* obj, int x) {
    if (!QueneEmpty(&obj->q1))
    {
        QueuePush(&obj->q1, x);
    }
    else
    {
        QueuePush(&obj->q2, x);
    }
}

int myStackPop(MyStack* obj) {
    //假设法
    pQueue empty = &obj->q1;
    pQueue nonempty = &obj->q2;
    if (!QueneEmpty(empty))
    {
        empty = &obj->q2;
        nonempty = &obj->q1;
    }
    while (nonempty->size > 1)
    {
        QueuePush(empty, QueueFront(nonempty));
        QueuePop(nonempty);
    }
    int top = QueueFront(nonempty);
    QueuePop(nonempty);
    return top;
}

int myStackTop(MyStack* obj) {
    if (!QueneEmpty(&obj->q1))
    {
        return QueneBack(&obj->q1);
    }
    else
    {
        return QueneBack(&obj->q2);
    }
}

bool myStackEmpty(MyStack* obj) {
    return QueneEmpty(&obj->q1) && QueneEmpty(&obj->q2);
}

void myStackFree(MyStack* obj) {
    QueueDestroy(&obj->q1);
    QueueDestroy(&obj->q2);
    free(obj);
}