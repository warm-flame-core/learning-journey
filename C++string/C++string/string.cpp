#include <iostream>
#include <string>
using namespace std;

// auto可以用于返回值但是不可以用于参数
auto func1()
{
	return 10;
}

// auto修饰，自动推导
void StringTest01()
{
	auto a = 10;
	auto b = a;
	auto c = func1();
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
}
//范围for,不引用是一种拷贝，不影响原来的值
void StringTest02()
{
	int arr[5] = { 1,2,3,4,5 };
	for (auto ch : arr)
	{
		ch++;
		cout << ch << " ";
	}
	cout << endl;
	//引用使用的时候就会修改原来的值
	for (auto &ch : arr)
	{
		ch+=2;
		cout << ch << " ";
	}


	cout << endl;
	for (auto ch : arr)
	{
		cout << ch << " ";
	}
	cout << endl;
}

// 字符串初始化的各种方法
void StringTest03()
{
	string s1;
	string s2("hello world");
	string s3(s2, 6, 5);	//从s2的索引6开始复制5个字符
	string s4(s2);
	string s5 = s4;
	string s6(s2, 6);		//从s2复制前6个字符
	string s7(6, 'c');		//6个位置都用C填充
	for (auto ch : s1)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s2)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s3)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s4)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s5)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s6)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s7)
	{
		cout << ch << " ";
	}
	cout << endl;

}

//迭代器,循环内修改会影响原来字符串
void StringTest04()
{
	string s1("Hello World");
	//正向迭代器
	//string::iterator it = s1.begin();
	auto it = s1.begin();
	while (it != s1.end())
	{
		//*it += 2;
		cout << *it << " ";
		++it;
	}
	cout << endl;
	cout << endl << endl;

	//cout << endl << endl;
	//for (auto ch : s1)
	//{
	//	cout << ch << " ";
	//}
	//cout << endl;

	//反向迭代器
	//string::reverse_iterator rit = s1.rbegin();
	auto rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	cout << endl << endl;

	const string s2 = s1;
	//const正向迭代器
	//string::const_iterator cit = s2.begin();
	auto cit = s2.begin();
	while (cit != s2.end())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
	cout << endl << endl;
	
	//const反向迭代器
	//string::const_reverse_iterator crit = s2.rbegin();
	auto crit = s2.rbegin();
	while (crit != s2.rend())
	{
		cout << *crit << " ";
		++crit;
	}
	cout << endl;
	cout << endl << endl;
}

void TestPushBack()
{
	// reverse 反转  逆置
	// reserve 保留、预留
	string s;
	// 提前开空间，避免扩容，提高效率
	//s.reserve(100);
	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';

	cout << "making s grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}


int main()
{
	
	//StringTest01();
	//StringTest02();
	//StringTest03();
	//StringTest04();
	//TestPushBack();
	return 0;
}