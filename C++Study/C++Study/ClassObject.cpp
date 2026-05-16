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


//#include "Date.h"
//void DateTest01()
//{
//	Date d1(2026, 5, 14);
//	
//	
//	/*d1 += 10000;
//	Date d2 = d1;
//	d2 = d1 + 1;*/
//
//	d1 -= 10000;
//	Date d2 = d1 - 1;
//	
//	d1.print();
//	d2.print();
//}
//void DateTest02()
//{
//	Date d1(2026, 5, 14);
//	Date d2 = d1 + 1;
//	cout << d2 - d1 << endl;
//}
//void DateTest03()
//{
//	Date d1, d2;
//	cin >> d1 >> d2;
//	cout << d1 << d2 << endl;
//}
//int main()
//{
//	DateTest03();
//	return 0;
//}


//初始化列表
#include <iostream>
using namespace std;
//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 9789)
//		//成员初始化，const引用的成员、没有默认构造的类类型成员、引用必须使用初始化列表
//		:_year(year)
//		, _mouth(month)
//		, _day(day)
//		//初始化顺序只和声明顺序有关
//	{}
//	Date(const Date& d)
//	{
//		_year = d._year;
//		_mouth = d._mouth;
//		_day = d._day;
//	}
//	void Print()
//	{
//		cout << _year << " " << _mouth << " " << _day << endl;
//	}
////定义
//private:
//	int _year = 2;
//	int _mouth = 0;
//	int _day = 867;
//};
////类类型成员最先看初始化列表，如果默认构造函数有赋值操作，那么函数体内部的操作会覆盖初始化列表
//int main()
//{
//	Date d1(1,8,5);
//	d1.Print();
//}


//类类型隐式类型转换
//class A
//{
//public:
//	A(int a = 0)
//	{
//		_a1 = a;
//	}
//	/*A(int a1 = 0, int a2 = 0)
//	{
//		_a1 = a1;
//		_a2 = a2;
//	}*/
//	void Print()
//	{
//		cout << _a1 << endl;
//	}
//private:
//	int _a1;
//	int _a2;
//};
//class Stack
//{
//public:
//	void Push(const A& aa)
//	{
//		//...
//	}
//private:
//	A _arr[10];
//	int _top;
//};
//
//int main()
//{
//	A aa1(1);
//	aa1.Print();
//
//	// 隐式类型转换
//	// 2构造一个A的临时对象，再用这个临时对象拷贝构造aa2
//	// 编译器遇到连续构造+拷贝构造->优化为直接构造
//	A aa2 = 2;
//	aa2.Print();
//
//	A& raa1 = aa2;
//	const A& raa2 = 2;
//
//	int i = 1;
//	double d = i;
//	const double& rd = i;
//
//	Stack st;
//
//	A aa3(3);
//	st.Push(aa3);
//
//	st.Push(3);
//
//	// C++11
//	/*A aa5 = { 1, 1 };
//	const A& raa6 = { 2,2 };
//	st.Push(aa5);
//	st.Push({ 2,2 });*/
//
//	return 0;
//}


//static 成员修饰
class A
{
public:
	A()
	{
		++_a;
	}
	~A()
	{
		--_a;
	}
	static int Get()
	{
		return _a;
	}
private:
	static int _a;
};

int A::_a = 0;

int main()
{
	A q1;
	cout << A::Get() << endl;
	A q2;
	
	cout << A::Get() << endl;
	return 0;
}