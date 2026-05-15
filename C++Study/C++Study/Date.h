#pragma once
#include <iostream>
using namespace std;
class Date
{
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& out, Date& d);
public:
	Date(int year = 1, int mouth = 1, int day = 1);
	void print();
    int GetMouthDay(int year, int mouth)
    {
        static int arr[13] = { -1,31,28,31,30,31,30,31,31,30,31,30,31 };
        if (mouth == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
        {
            return 29;
        }
        return arr[mouth];
    }
    bool CheckDate();
    bool operator<(const Date& d) const;
    bool operator<=(const Date& d) const;
    bool operator>(const Date& d) const;
    bool operator>=(const Date& d) const;
    bool operator==(const Date& d) const;
    bool operator!=(const Date& d) const;
    // d1 += 天数

    Date& operator+=(int day);
    Date operator+(int day) const;
    // d1 -= 天数

    Date& operator-=(int day);
    Date operator-(int day) const;
    // d1 - d2
    int operator-(const Date& d) const;
    // ++d1 -> d1.operator++()
    Date& operator++();
    // d1++ -> d1.operator++(0)
    Date operator++(int);
    Date& operator--();
    Date operator--(int);
private:
	int _year;
	int _mouth;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& out, Date& d);