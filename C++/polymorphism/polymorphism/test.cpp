#include <iostream>
using namespace std;

// 多态：基类用虚函数，子类重写虚函数，用基类的指针或者应用调用
// 子类中需要重写的函数可以不用加virtual
//class Person
//{
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//
//class Student : public Person {
//public:
//	void BuyTicket() { cout << "买票-打折" << endl; }
//};
//void Func(Person& ptr)
//{
//	ptr.BuyTicket();
//}
//
//int main()
//{
//	Person p1;
//	Student s1;
//	Func(p1);
//	Func(s1);
//	return 0;
//}



// 构成重写只重写虚函数的定义，所以重写应该保持缺省值不变
//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//
//class B : public A
//{
//public:
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	// B类没有重写test，所以调用的是A类的，func是继承且构成重写，编译时在A类查找到test函数，调用func的时候也是从A类确定缺省值，所以用A的缺省值执行B的函数
//	p->test();
//	// B类型优先在B里面找
//	p->func();
//
//	return 0;
//}


// 只要是基类对基类，子类对子类就可以
//class A {};
//class B : public A {};
//class Person {
//public:
//	virtual A* BuyTicket()
//	{
//		cout << "买票-全价" << endl;
//		return nullptr;
//	}
//};
//
//class Student : public Person {
//public:
//	virtual B* BuyTicket()
//	{
//		cout << "买票-打折" << endl;
//		return nullptr;
//	}
//};
//
//void Func(Person* ptr)
//{
//	ptr->BuyTicket();
//}
//
//int main()
//{
//	Person ps;
//	Student st;
//
//	Func(&ps);
//	Func(&st);
//
//	return 0;
//}


class A
{
public:
	virtual ~A()
	{
		cout << "~A()" << endl;
	}
};

class B : public A {
public:
	// 构成重写
	~B()
	{
		cout << "~B()->delete:" << _p << endl;
		delete _p;
	}
protected:
	int* _p = new int[10];
};
int main()
{
	// 多态需要用基类的指针或者引用，如果子类存在自定义类型且析构不用虚函数，析构的时候只会调用基类，子类造成内存泄漏
	A* p1 = new A;
	A* p2 = new B;
	delete p1;
	delete p2;
	return 0;
}