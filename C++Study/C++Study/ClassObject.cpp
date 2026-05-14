//#define _CRT_SECURE_NO_WARNINGS 1
//#include <iostream>
//using namespace std;
//class Date
//{
//public:
//	void Init(int year = 10, int mouth = 10, int day = 10)
//	{
//		this->_mouth = mouth;
//		this->_year = year;
//		this->_day = day;
//	}
//	void Print()
//	{
//		cout << _year << " " << _mouth << " " << _day << endl;
//	}
//private:
//	int _year;
//	int _mouth;
//	int _day;
//};
//int main()
//{
//	Date d1;
//	d1.Init();
//	d1.Print();
//	return 0;
//}


//class Date
//{
//public:
//	Date()
//	{
//		_year = 1;
//		_mouth = 1;
//		_day = 1;
//	}
//	Date(int year, int month, int day)
//	{
//		_year = year;
//		_mouth = month;
//		_day = day;
//	}
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_mouth = month;
//		_day = day;
//	}
//	void Print()
//	{
//		cout << _year << " " << _mouth << " " << _day << endl;
//	}
//private:
//	int _year;
//	int _mouth;
//	int _day;
//};
//
//int main()
//{
//	Date d1(2026,5,11);
//	d1.Print();
//	return 0;
//}


//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//				return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//private:
//	STDataType* _a;
//	size_t _capacity;
//	size_t _top;
//};
//
////内置类型构造时不确定，自定义类型会看自定义类型的构造
//class MyQueue
//{
//public:
//	//编译器默认?成MyQueue的构造函数调用了Stack的构造，完成了两个成员的初始化
//private:
//	Stack pushst;
//	Stack popst;
//};

//析构函数
//typedef int STDataType;
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		_a = (STDataType*)malloc(sizeof(STDataType) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//	~Stack()
//	{
//		cout << "~Stack" << endl;
//		free(_a);
//		_a = nullptr;
//		_top = _capacity = 0;
//	}
//private:
//	STDataType* _a;
//	size_t _capacity;
//	size_t _top;
//};
//
////内置类型构造时不确定，自定义类型会看自定义类型的构造
//class MyQueue
//{
//public:
//	//编译器默认生成MyQueue的构造函数调?了Stack的构造，完成了两个成员的初始化
//	//编译器默认生成MyQueue的析构函数调用了Stack的析构，销毁了两个成员
//private:
//	Stack pushst;
//	Stack popst;
//};
//
//int main()
//{
//	MyQueue m;
//	
//	return 0;
//}


//拷贝构造函数
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_mouth = month;
//		_day = day;
//	}
//	Date(const Date& d)//函数默认还有一个this指针，不显式写，且参数应该是引用，防止无穷递归
//	//自定义类型传值传参会调用拷贝构造
//	{
//		_year = d._year;
//		_mouth = d._mouth;
//		_day = d._day;
//	}
//	Date(Date* d)//不是拷贝构造，就是普通的构造函数
//	{
//		_year = d->_year;
//		_mouth = d->_mouth;
//		_day = d->_day;
//	}
//	void Print()
//	{
//		cout << _year << " " << _mouth << " " << _day << endl;
//	}
//private:
//	int _year;
//	int _mouth;
//	int _day;
//};
//
//int main()
//{
//	Date d1(2026,5,11);
//	d1.Print();
//	Date d2(d1);
//	d2.Print();
//	Date d3(&d1);
//	d3.Print();
//	return 0;
//}

//#include <stdbool.h>
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//	{
//		_year = year;
//		_mouth = month;
//		_day = day;
//	}
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_mouth = d._mouth;
//		_day = d._day;
//	}
//
//	bool operator==(Date& d2)
//	{
//		return _year == d2._year
//			&& _mouth == d2._mouth
//			&& _day == d2._day;
//	}
//
//	bool operator!=(Date& d2)
//	{
//		return !(*this == d2);
//	}
//	
//	void Print()
//	{
//		cout << _year << "-" << _mouth << "-" << _day << endl;
//	}
//private:
//	int _year;
//	int _mouth;
//	int _day;
//};

//bool operator==(const Date& d1, Date& d2)
//{
//	return d1._year == d2._year
//		&& d1._mouth == d2._mouth
//		&& d1._day == d2._day;
//}

//int main()
//{
//	Date d1(2026, 5, 13);
//	Date d2 = d1;
//	d1 == d2;
//	d1.Print();
//	d2.Print();
//	return 0;
//}


#include "Date.h"
void DateTest01()
{
	Date d1(2026, 5, 14);
	
	
	/*d1 += 10000;
	Date d2 = d1;
	d2 = d1 + 1;*/

	d1 -= 10000;
	Date d2 = d1 - 1;
	
	d1.print();
	d2.print();
}
void DateTest02()
{
	Date d1(2026, 5, 14);
	Date d2 = d1 + 1;
	cout << d2 - d1 << endl;
}
void DateTest03()
{
	Date d1, d2;
	cin >> d1 >> d2;
	cout << d1 << d2 << endl;
}
int main()
{
	DateTest03();
	return 0;
}