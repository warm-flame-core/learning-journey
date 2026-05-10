#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
class Date
{
public:
	void Init(int year = 10, int mouth = 10, int day = 10)
	{
		this->_mouth = mouth;
		this->_year = year;
		this->_day = day;
	}
	void Print()
	{
		cout << _year << " " << _mouth << " " << _day << endl;
	}
private:
	int _year;
	int _mouth;
	int _day;
};
int main()
{
	Date d1;
	d1.Init();
	d1.Print();
	return 0;
}