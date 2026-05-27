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
	for (auto ch : arr)
	{
		cout << ch << " ";
	}
	cout << endl;
}
int main()
{
	//StringTest01();
	StringTest02();
	return 0;
}