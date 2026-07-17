#include <iostream>
#include "PriorityQueue.h"
using namespace std;

// 模板可以定义非类型形参，本质是一个常量，std里有一个库array用的就是带有常量
// array越界读写都可以检查，普通数组越界读不检查，越界写抽查
namespace xjw
{
	template<class T, size_t N = 10>
	class array
	{
	public:
		T& operator[](size_t index) { return _array[index]; }
		const T& operator[](size_t index)const { return _array[index]; }
		size_t size()const { return _size; }
		bool empty()const { return 0 == _size; }
	private:
		T _array[N];
		size_t _size;
	};
}

// 日期类
class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}

	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}
template<class T>
bool LessFunc(const T& left, const T& right)
{
	return left < right;
}
// 如果是指针所希望的比较是解引用再比较
// 函数模板特化

// 原模板const修饰的是形参，这里的const在*的左边修饰的是指针指向的内容
//template<>
//bool LessFunc<Date*>(const Date*& left, const Date*& right)
//{
//	return *left < *right;
//}

template<>
bool LessFunc<Date*>(Date* const& left, Date* const& right)
{
	return *left < *right;
}
template<>
bool LessFunc<const Date*>(const Date* const& left,const Date* const& right)
{
	return *left < *right;
}


// 类模板的特化
template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
// 全特化
template<>
class Data<int, double>
{
public:
	Data() { cout << "Data<int, double>" << endl; }
};
// 偏特化
template<class T1>
class Data<T1, double>
{
public:
	Data() { cout << "Data<T1, double>" << endl; }
};
// 模板参数是指针也属于偏特化
// 且模板参数传指针，但是T1和T2是基类型，目的是为了分辨const
template <typename T1, typename T2>
class Data <T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}
};
// 引用也是偏特化
template <typename T1, typename T2>
class Data <T1&, T2&>
{
public:
	Data()
	{
		cout << "Data<T1&, T2&>" << endl;
	}
};

template <typename T1, typename T2>
class Data <T1&, T2*>
{
public:
	Data()
	{
		cout << "Data<T1&, T2*>" << endl;
	}

	void Push(const T1& x)
	{}
};

// const int * 不能解引用修改基类型的值，但是可以修改指向
// int * const 不能修改指向，但是可以修改基类型的值
//int main()
//{
//	/*xjw::array<int, 100> a1;
//	cout << a1.empty() << endl;*/
//
//	cout << LessFunc(1, 2) << endl; // 可以比较，结果正确
//
//	Date d1(2022, 7, 7);
//	Date d2(2022, 7, 8);
//	cout << LessFunc(d1, d2) << endl; // 可以比较，结果正确
//
//	Date* p1 = &d1;
//	Date* p2 = &d2;
//	cout << LessFunc(p1, p2) << endl; // 可以比较，结果错误
//
//	const Date* p3 = &d1;
//	const Date* p4 = &d2;
//	cout << LessFunc(p3, p4) << endl; // 可以比较，结果错误
//
//	return 0;
//}


int main()
{
	Data<int, int> d1;
	Data<int, char> d2;
	Data<int, double> d3;
	Data<char, double> d4;
	Data<char, char> d5;
	Data<char*, char*> d6;
	Data<int*, char*> d7;
	Data<int&, char&> d8;
	Data<int&, double&> d9;
	Data<int&, int*> d10;

	return 0;
}