#define _CRT_SECURE_NO_WARNINGS 1
//#include <stdio.h>
////命名空间
//namespace wfc
//{
//	int rand = 10;
//	int Add(int a, int b)
//	{
//		return a + b;
//	}
//	
//	/*namespace xie
//	{
//		int rand = 50;
//	}*/
//
//}
//using wfc::rand;
//int main()
//{
//	printf("%d\n", rand);
//	printf("%d\n", wfc::Add(1, 2));
//	/*printf("%d\n", wfc::xie::rand);*/
//	return 0;
//}


//输入和输出
#include <iostream>
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
//int Add(int a, int b = 10)
//{
//	return a + b;
//}
//
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