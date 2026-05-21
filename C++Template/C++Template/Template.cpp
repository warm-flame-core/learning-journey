#include <iostream>
using namespace std;
template<class T>
T Add(const T& x, const T& y)
{
	return x + y;
}

template<class T1, class T2>
void Swap(T1& a, T2& b)
{
	T1 tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
class Stack
{
public:
	Stack(int n = 4)
		:_arr(new T[n])
		,_top(0)
		,_capacity(n)
	{}
	~Stack()
	{
		delete[] _arr;
		_arr = nullptr;
		_top = _capacity = 0;
	}
private:
	T* _arr;
	size_t _top;
	size_t _capacity;
};

int main()
{
	//<隐式推导实例化>
	cout << Add(1, 3) << endl;
	cout << Add(1.1, 3.3) << endl;
	//显式推导实例化
	cout << Add<double>(1, 2) << endl;
}