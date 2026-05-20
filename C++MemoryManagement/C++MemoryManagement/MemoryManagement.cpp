#include <iostream>
using namespace std;
class A
{
public:
	A(int a1 = 10, int a2 = 10)
		:_a1(a1)
		, _a2(a2)
	{
		cout << "A():" << this << endl;
	}
	~A()
	{
		cout << "~A():" << this << endl;
		_a1 = 0;
	}
private:
	int _a1;
	int _a2;
};

class B
{
public:
	/*~B()
	{
		cout << "~B()" << endl;
	}*/
private:
	int _b1 = 2;
	int _b2 = 2;
};

//int main()
//{
//	int* p1 = new int(1);
//	cout << *p1 << endl;
//	A* pa1 = new A;
//	A* pa2 = new A[10];
//	delete pa1;
//	delete[] pa2;
//	A aa1(1, 1);
//	A aa2(2, 2);
//	A aa3(3, 3);
//	A* pa4 = new A[3]{ aa1,aa2,aa3 };	//多参数申请空间
//	A* pa5 = new A[3]{ A(1,1),A(2,2), A(3,3) };
//	A* pa6 = new A[3]{ {1,1},{2,2},{3,3} };
//	delete[] pa4;
//	delete[] pa5;
//	delete[] pa6;
//	return 0;
//}

int main()
{
	//int* p1 = new int[10]; // -> malloc
	//delete p1;             // -> free
	//free(p1);


	// new多个对象的时候会在头存数组个数，不带【】delete时不能全部释放，只会析构一次，且带头的数据会被落下，造成释放不完全
	// 类里面不显式写析构，编译器就不会在头位置存数组个数
	B* p2 = new B[10];
	delete p2;

	//A* p3 = new A[10];
	//delete[] p3;
	return 0;
}