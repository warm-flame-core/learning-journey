#include<iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

void list_test01()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	list<int>::iterator it = lt.begin();
	while (it != lt.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	for (int e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}
// list是双向迭代器，只有++和--
struct A
{
public:
	A(int a1 = 1, int a2 = 1)
		:_a1(a1)
		, _a2(a2)
	{
		cout << "A(int a1 = 1, int a2 = 1)" << endl;
	}

	A(const A& aa)
		:_a1(aa._a1)
		, _a2(aa._a2)
	{
		cout << "A(const A& aa)" << endl;
	}

	int _a1;
	int _a2;
};

void test_list2()
{
	list<int> lt;
	lt.push_back(1);
	lt.emplace_back(2);
	lt.emplace_back(3);
	lt.emplace_back(4);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	list<A> lt1;
	A aa1(1, 1);
	lt1.push_back(aa1);
	lt1.push_back(A(2, 2));
	//lt.push_back(3, 3);

	lt1.emplace_back(aa1);
	lt1.emplace_back(A(2, 2));
	cout << endl;
	// 支持直接传构造A对象的参数emplace_back,用匿名对象
	lt1.emplace_back(3, 3);
}

void test_list3()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
	auto it = lt.begin();
	int k = 3;
	while (k--)
	{
		it++;
	}
	lt.insert(it, 20);
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;

	int x = 0;
	cin >> x;
	it = find(lt.begin(), lt.end(), x);
	lt.erase(it);
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void test_list4()
{
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(20);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);
	// 用仿函数和匿名对象实现降序
	lt.sort(greater<int>());
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
	lt.reverse();
	lt.sort(greater<int>());
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
	reverse(lt.begin(), lt.end());
	for (auto e : lt)
	{
		cout << e << ' ';
	}
	cout << endl;
}

void test_list5()
{
	std::list<double> first, second;

	first.push_back(3.1);
	first.push_back(2.2);
	first.push_back(2.9);

	second.push_back(3.7);
	second.push_back(7.1);
	second.push_back(1.4);

	first.sort();
	second.sort();

	first.merge(second);

}

void test_list6()
{
	// 一个链表节点转移给另一个链表
	std::list<int> mylist1, mylist2;
	std::list<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i);      // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10);   // mylist2: 10 20 30

	it = mylist1.begin();
	++it;                         // points to 2

	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
	// mylist2 (empty)
	// "it" still points to 2 (the 5th element


// 调整当前链表节点的顺序
	list<int> lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;

	int x = 0;
	cin >> x;
	it = find(lt.begin(), lt.end(), x);
	if (it != lt.end())
	{
		//lt.splice(lt.begin(), lt, it);
		lt.splice(lt.begin(), lt, it, lt.end());
	}

	for (auto e : lt)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test_op2()
{
	srand(time(0));
	const int N = 1000000;

	list<int> lt1;
	list<int> lt2;

	for (int i = 0; i < N; ++i)
	{
		auto e = rand() + i;
		lt1.push_back(e);
		lt2.push_back(e);
	}

	int begin1 = clock();
	// 拷贝vector
	vector<int> v(lt2.begin(), lt2.end());

	// 排序
	sort(v.begin(), v.end());

	// 拷贝回lt2
	lt2.assign(v.begin(), v.end());

	int end1 = clock();

	int begin2 = clock();
	lt1.sort();
	int end2 = clock();

	printf("list copy vector sort copy list sort:%d\n", end1 - begin1);
	printf("list sort:%d\n", end2 - begin2);
}

int main()
{
	//test_list5();
	test_op2();
	return 0;
}