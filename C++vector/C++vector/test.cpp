#include <iostream>
#include <vector>
using namespace std;
void test_vector1()
{
	vector<int> v(10, 1);
	vector<int> v2(10, 2);
	// 迭代器构造
	vector<int> v3(++v2.begin(), --v2.end());
	for (auto e : v)
	{
		cout << e << endl;
	}
	cout << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void TestVectorExpand()
{
	size_t sz;
	vector<int> v;
	//v.reserve(100);

	sz = v.capacity();
	cout << "capacity changed: " << sz << '\n';

	cout << "making v grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		v.push_back(i);
		if (sz != v.capacity())
		{
			sz = v.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

void test_vector2()
{
	//TestVectorExpand();

	vector<int> v(10, 1);
	v.reserve(20);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(15);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.reserve(5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void test_vector3()
{
	//TestVectorExpand();

	vector<int> v(10, 1);
	v.reserve(20);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	//resize过短会截断
	v.resize(15, 2);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(25, 3);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(5);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void test_vector4()
{
	vector<int> v(10, 1);
	v.insert(v.begin() + 2, 3);
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
	v.erase(v.begin() + 1, v.end() - 1);
	for (auto e : v)
	{
		cout << e << ' ';
	}
	cout << endl;
}


//int main()
//{
//	//test_vector1();
//	//TestVectorExpand();
//	//test_vector2();
//	//test_vector3();
//	test_vector4();
//	return 0;
//}

#include "vector.h"
int main()
{
	//xjw::my_vector_test01();
	xjw::my_vector_test03();
}