#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>

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

		iterator rbegin() const
		{
			return _str;
		}

		iterator rend() const
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

		~string()
		{
			delete[] _str;
			_size = _capacity = 0;
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

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}