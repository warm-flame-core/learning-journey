#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"
Date::Date(int year, int mouth, int day)	// 缺省值在定义的时候显式
{
	_year = year;
	_mouth = mouth;
	_day = day;

	if (!(CheckDate()))
	{
		cout << "日期非法：";
		print();
	}
}

void Date::print()
{
	cout << _year << "/" << _mouth << "/" << _day << endl;
}

bool Date::CheckDate()
{
	if (_mouth < 1 || _mouth > 12|| _day < 1 || _day > GetMouthDay(_year, _mouth))
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool Date::operator<(const Date& d)
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year)
	{
		if (_mouth < d._mouth)
			return true;
		else if (_mouth == d._mouth)
		{
			return _day < d._day;
		}
	}
	return false;
}
bool Date::operator<=(const Date& d)
{
	return *this < d || *this == d;
}
bool Date::operator>(const Date& d)
{
	return !(*this <= d);
}
bool Date::operator>=(const Date& d)
{
	return !(*this < d);
}
bool Date::operator==(const Date& d)
{
	return _year == d._year
		&& _mouth == d._mouth
		&& _day == d._day;
}
bool Date::operator!=(const Date& d)
{
	return !(*this == d);
}

// 效率更高，让+去复用+=的功能
// 传值返回，因为需要带出tmp，tmp是局部变量出作用域会销毁，需要拷贝构造

//+喜欢克隆，其他运算符重载如果调用+很容易出现局部变量出作用域销毁，尽量少用+去复用其他运算符
Date Date::operator+(int day)
{
	Date tmp = *this;	// 调用拷贝构造
	return tmp += day;
}
// 传引用返回，因为this指针所指向的是作用域外的变量，传引用返回减少拷贝
Date& Date::operator+=(int day)
{

	_day += day;
	while (_day > Date::GetMouthDay(_year, _mouth))
	{
		_day -= Date::GetMouthDay(_year, _mouth);
		++_mouth;
		if (_mouth == 13)
		{
			_mouth = 1;
			++_year;
		}
	}
	return *this;
}

//这样的写法效率比较低,比上面多一次拷贝和赋值
//Date Date::operator+(int day)
//{
//	Date tmp = *this;	//调用拷贝构造
//	tmp._day += day;
//	while (tmp._day > Date::GetMouthDay(tmp._year, tmp._mouth))
//	{
//		tmp._day -= Date::GetMouthDay(tmp._year, tmp._mouth);
//		++tmp._mouth;
//		if (tmp._mouth == 13)
//		{
//			tmp._mouth = 1;
//			++tmp._year;
//		}
//	}
//	return tmp;		// 传值返回调用拷贝构造
//}
//Date& Date::operator+=(int day)
//{
//	*this = *this + day;	// 等于操作调用赋值重载
//	return *this;
//}


Date& Date::operator-=(int day)
{
	_day -= day;
	while (_day <= 0)
	{
		--_mouth;
		if (_mouth == 0)
		{
			_mouth = 12;
			--_year;
		}
		_day += Date::GetMouthDay(_year, _mouth);
	}
	return *this;
}
Date Date::operator-(int day)
{
	Date tmp = *this;
	tmp -= day;
	return tmp;
}

int Date::operator-(const Date& d)
{
	// 假设法，如果假设正确是大-小，那么返回整数，如果假设错误，返回差值的负数
	int flag = 1;
	Date max = *this;
	Date min = d;
	if (min > max)
	{
		max = d;
		min = *this;
		flag = -1;
	}
	int n = 0;
	while (min != max)
	{
		++n;
		++min;
	}
	return n * flag;
}

//前置的自增or自减形参不写，后置的写一个int形参区别分开

// 前置++
// 使用+的复用，返回的是局部变量，会出现空应用
//Date& Date::operator++()
//{
//	return (*this) + 1;
//}

Date& Date::operator++()
{
	*this += 1; 
	return *this; 
}
Date Date::operator++(int)
{
	Date tmp = *this;
	*this+=1;
	return tmp;
}

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;
	return tmp;
}

ostream& operator<<(ostream& out, const Date& d)
{
	cout << d._year << "年" << d._mouth << "月" << d._day << "日" << endl;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		cout << "请依次输入日期:>";
		in >> d._year >> d._mouth >> d._day;
		if (!(d.CheckDate()))
		{
			cout << "日期无效,重新输入" << endl;
		}
		else
			break;
	}
	return in;
}