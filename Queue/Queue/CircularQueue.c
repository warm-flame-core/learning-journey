#define _CRT_SECURE_NO_WARNINGS 1
#include "Queue.h"

//循环队列实现，对应LeetCode第622题
typedef struct {
    int* a;
    int head;
    int tail;
    int k;
} MyCircularQueue;

bool myCircularQueueIsEmpty(MyCircularQueue* obj);

bool myCircularQueueIsFull(MyCircularQueue* obj);
MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* Queue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    Queue->a = (int*)malloc(sizeof(int) * (k + 1));
    Queue->head = Queue->head = 0;
    Queue->k = k;
    return Queue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if (myCircularQueueIsFull(obj))
        return false;
    else
    {
        obj->a[obj->tail] = value;
        obj->tail++;
    }
    obj->tail %= (obj->k + 1);
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))
    {
        return false;
    }
    else
    {
        obj->head++;
    }
    obj->tail %= (obj->k + 1);
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))
    {
        return -1;
    }
    else
        return obj->a[obj->head];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if (myCircularQueueIsEmpty(obj))
    {
        return -1;
    }
    else
    {
        int rear = obj->tail == 0 ? obj->k : obj->tail - 1;
        return obj->a[rear];
    }
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->tail == obj->head;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return (obj->tail + 1) % (obj->k + 1) == obj->head;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->a);
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);

 * bool param_2 = myCircularQueueDeQueue(obj);

 * int param_3 = myCircularQueueFront(obj);

 * int param_4 = myCircularQueueRear(obj);

 * bool param_5 = myCircularQueueIsEmpty(obj);

 * bool param_6 = myCircularQueueIsFull(obj);

 * myCircularQueueFree(obj);
*/