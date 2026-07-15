#include <iostream>
#include <stack>
#include <queue>
#include <functional>
using namespace std;
#include"stack.h"
#include "queue.h"
#include "PriorityQueue.h"
void stack_test1()
{
	xjw::stack<int> s1;
	s1.push(1);
	s1.push(2);
	s1.push(3);
	s1.push(4);
	s1.push(5);

}

void stack_test2()
{
	xjw::stack<int> st1;
	xjw::stack<int> st2 = st1;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);
	st1.push(5);
	st1.push(6);
	st2.push(7);
	st2.push(8);
	st2.push(9);
	st2.push(10);
	st2.push(11);
	cout << st1.top() << endl;
	st1.pop();
	cout << st1.empty() << endl;
}


//PriorityQueue
void testPriorityQueue1()
{
	vector<int> v{ 3,2,7,6,0,4,1,9,8,5 };
	// 默认是less，大堆
	xjw::priority_queue<int> q1;
	for (auto e : v)
	{
		q1.push(e);
	}
	// 如果要小堆需要greater
	priority_queue<int, vector<int>, greater<int>> q2(v.begin(), v.end());
}

int main()
{
	//stack_test2();
	testPriorityQueue1();
	return 0;
}