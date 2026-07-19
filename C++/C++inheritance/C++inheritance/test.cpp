#include <iostream>
#include<vector>
#include<list>
#include<deque>
using namespace std;

// 继承
//class Person
//{
//public:
//	// 进入校园/图书馆/实验室刷二维码等身份认证
//	void identity()
//	{
//		cout << "void identity()" << _name << endl;
//		cout << _age << endl;
//	}
//protected:
//	string _name = "张三"; // 姓名
//	string _address; // 地址
//	string _tel; // 电话
//private:
//	int _age = 18; // 年龄
//};
//
//class Student : public Person
//{
//public:
//	// 学习
//	void study()
//	{
//		identity();
//		// ...
//		//cout << _age << endl;
//		cout << _tel << endl;
//	}
//protected:
//	int _stuid; // 学号
//};
//
//class Teacher : public Person
//{
//public:
//	// 授课
//	void teaching()
//	{
//		//...
//	}
//protected:
//	string title; // 职称
//};

//int main()
//{
//	Student s;
//	Teacher t;
//
//	s.identity();
//	t.identity();
//
//	return 0;
//}

// 栈的实现既可以用组合也可以用继承
//namespace xjw
//{
//	template<class T>
//	class stack : public vector<T>
//	{
//	public:
//		void push(const T& x)
//		{
//			vector<T>::push_back(x);
//		}
//		void pop()
//		{
//			vector<T>::pop_back();
//		}
//		const T& top()
//		{
//			return vector<T>::back();
//		}
//		bool empty()
//		{
//			return vector<T>::empty();
//		}
//	};
//}
//
//
//int main()
//{
//	xjw::stack<int> st1;
//	st1.push(1);
//	st1.push(2);
//	st1.push(3);
//	st1.push(4);
//	st1.push(5);
//	st1.push(6);
//	st1.push(7);
//	return 0;
//}



//class Person
//{
////protected:
//	virtual void func()
//	{}
//public:
//	string _name; // 姓名
//	string _sex; // 性别
//	int _age; // 年龄
//};
//
//class Student : public Person
//{
//public:
//	int _No; // 学号
//	int _age;
//};
//
//int main()
//{
//	Student sobj;
//
//	// 子类对象可以赋值给父类对象/指针/引用，不是隐式类型转换
//	Person pobj = sobj;
//	Person* pp = &sobj;
//	Person& rp = sobj;
//	rp._name = "张三";
//
//	int i = 1;
//	double d = i;
//	const double& rd = i;
//
//	// 父类对象不能赋值给子类对象，这里会编译报错，强制类型转换也不行
//	//sobj = (Student)pobj;
//
//	//同名成员构成隐藏，如果要访问基类成员函数要限定：：
//	cout << sobj._age << endl;
//
//	return 0;
//}


// 派生类中的默认成员函数
class Person
{
public:
	Person(const char* name = "xxx")
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;
		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	string _name; // 姓名
};

class Student : public Person
{
public:
	Student(const char* name, int num, const char* addrss)
		:Person(name)
		, _num(num)
		, _addrss(addrss)
	{}

	// 如果有需要深拷贝的资源，需要自己实现
	Student(const Student& s)
		// 调用的时候要把父类看成一个自定义类型调用对应的构造函数
		:Person(s)
		, _num(s._num)
		, _addrss(s._addrss)
	{
		// 深拷贝
	}

	Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			// 父类和子类的operator=构成隐藏关系
			Person::operator=(s);

			_num = s._num;
			_addrss = s._addrss;
		}

		return *this;
	}

	// 析构函数都会被特殊处理成destructor() 
	// 基类和派生类的析构函数也构成隐藏
	~Student()
	{
		//不需要显示调用，子类析构函数之后，会自动调用父类析构
		// 这样保证析构顺序，先子后父，显示调用取决于实现的人，不能保证先子后父
		// 
		//Person::~Person();
		//delete _ptr;
	}
protected:
	int _num = 1; //学号
	string _addrss = "赣州市";

	int* _ptr = new int[10];
};

int main()
{
	Student s1("张三", 1, "赣州市");
	Student s2(s1);

	Student s3("李四", 2, "章贡区");
	s1 = s3;

	/*Person* ptr = new Person;
	delete ptr;*/

	return 0;
}