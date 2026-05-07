#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
//命名空间
//namespace wfc
//{
//	namespace xie
//	{
//		int rand = 10;
//		int Add(int a, int b)
//		{
//			return a + b;
//		}
//	}
//}
//using wfc::xie::rand;
//int main()
//{
//	printf("%d\n", rand);
//	printf("%d\n", wfc::xie::Add(1, 2));
//	return 0;
//}

//输入和输出
//#include <iostream>
//using namespace std;
//int main()
//{
//	int a = 0;
//	double b = 1.11;
//	char c = 'x';
//	std::cout << a << " " << b << c <<std::endl;
//	std::cin >> a >> b >> c;
//	std::cout << a << " " << b << c << std::endl;
//	return 0;
//}


//int main()
//{
//	std::ios_base::sync_with_stdio(false);
//	std::cin.tie(nullptr);
//	std::cout.tie(nullptr);
//	return 0;
//}


//缺省参数、函数重载
#include <iostream>
using namespace std;
//void Func2(int a, int b = 10, int c = 20)
//{
//	cout << "a = " << a << endl;
//	cout << "b = " << b << endl;
//	cout << "c = " << c << endl << endl;
//}
//int Add(int a, int b = 10)
//{
//	return a + b;
//}

//int Add(int left, int right)
//{
//	cout << "int Add(int left, int right)" << endl;
//	return left + right;
//}
//double Add(double left, double right)
//{
//	cout << "double Add(double left, double right)" << endl;
//	return left + right;
//}

//void f()
//{
//	cout << "f()" << endl;
//}
//void f(int a)
//{
//	cout << "f(int a)" << endl;
//}

//void f1()
//{
//	cout << "f1()" << endl;
//}
//void f1(int a = 10)
//{
//	cout << "f1()" << endl;
//}

//double Add(double a, double b = 10)
//{
//	return a + b;
//}
//
//int main()
//{
//	std::cout << Add(1) << std::endl;
//}


//引用
using namespace std;
void Swap(int& ra, int& rb)
{
	int tmp = ra;
	ra = rb;
	rb = tmp;
}
int main()
{
	int a = 10;
	int b = 20;
	int& d = a;
	/*d = b;*/	//引用不可以改变指向
	Swap(a, b);
	cout << a << b << endl;
	return 0;
}


//counst修饰
//int main()
//{
//	const int a = 10;
//	const int& ra = a;	//权限平移
//
//	int b = 20;
//	const int& rb = b;	//权限缩小
//	//rb++;
//
//	//int& rc = a + b;	//创建了临时变量不可以引用
//
//	const int& rc = a + b;	//可以对只读的变量进行const修饰的引用
//
//	return 0;
//}


//内联
//#define ADD(a, b) ((a) + (b))
//int main()
//{
//	int ret = ADD(1, 3);
//	cout << ret << endl;
//	return 0;
//}
//inline int Add(int a, int b)
//{
//	return a + b;
//}
//
//int main()
//{
//	int ret = Add(1, 3);
//	return 0;
//}


//nullptr指针
//#include <iostream>
//using namespace std;
//void fun(int x)
//{
//	cout << "fun(int x)" << endl;
//}
//void fun(int* x)
//{
//	cout << "fun(int* x)" << endl;
//}
//int main()
//{
//	fun(0);
//	fun((int*)NULL);
//	//fun((void*)NULL);
//	fun(nullptr);
//	return 0;
//}