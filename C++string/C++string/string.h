#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

namespace xjw
{
	class string
	{
	public:
		// 迭代器命名
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		size_t size() const
		{
			return _size;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		string& operator=(const string& str)
		{
			if (this != &str)	// 考虑自己等于自己，不能把自己删除了
			{
				delete[] _str;	// 要赋值的字符串可能是已经有字符的字符串，需要先清除
				_str = new char[str._capacity + 1];
				strcpy(_str, str._str);
				_size = str._size;
				_capacity = str._capacity;
				return *this;
			}
		}

		// 重载方括号
		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		// 两种构造可以写一起
		/*string()
			:_str(new char[1]{'\0'})
			,_size(0)
			,_capacity(0)
		{}*/
		
		// 不可以用先初始化_size，因为初始化列表顺序取决于成员定义的顺序
		/*string(const char* str = "")
			:_str(new char[strlen(str) + 1])
			,_size(strlen(str))
			,_capacity(strlen(str))
		{}*/

		string(const char* str = "")
		{
			// 不传递0和空指针，可能会解引用
			_size = strlen(str);
			_capacity = _size;	// capacity不包括\0
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		// 赋值拷贝构造
		// 传统写法
		/*string(const string& str)
		{
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
			_size = str._size;
			_capacity = str._capacity;
		}*/
		// 现代写法
		// 深拷贝str的字符串，其他都用缺省值的tmp，与
		string(const string& str)
		{
			string tmp(str._str);
			swap(tmp);
		}

		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//s1.swap(str)
		void swap(string& str)
		{
			_str = new char[str.capacity() + 1];
			std::swap(_str, str._str);
			std::swap(_size, str._size);
			std::swap(_capacity, str._capacity);
		}

		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}

		char* c_str()	const
		{
			return _str;
		}
		void reserve(size_t n);					// 调整大小
		void push_back(char ch);				// 尾插一个字符
		string& operator+=(char ch);			// 重载运算符+=
		string& operator+=(const char* str);	
		void append(const char* str);			// 追加一个字符串
		void insert(size_t pos, char ch);		// 前下标pos之前插入一个字符
		void insert(size_t pos,const char* str);// 前下标pos之前插入一个字符串
		size_t find(char ch, size_t pos = 0);
		size_t find(const char* str, size_t pos = 0);
		string substr(size_t pos = 0, size_t len = npos);

	private:
		// 给缺省值方便用现代写法
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;

		// 静态的整形最特殊，可以直接给初始值，但是还是建议类外面写默认值
		/*static const size_t npos = -1;
		static const int n = -1;*/

		static const size_t npos;
	};
	bool operator<(const string& s1, const string& s2);
	bool operator<=(const string& s1, const string& s2);
	bool operator>(const string& s1, const string& s2);
	bool operator>=(const string& s1, const string& s2);
	bool operator==(const string& s1, const string& s2);
	bool operator!=(const string& s1, const string& s2);

	ostream& operator<<(ostream& out, const string& s);
	istream& operator>>(istream& in, string& s);
}