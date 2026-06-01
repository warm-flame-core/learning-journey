#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"
namespace xjw
{
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}

	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	string& string::operator+=(char ch)
	{
		this->push_back(ch);
		return *this;
	}


	// 常把返回信息更少、功能更单一的函数作为“底层实现”，让返回信息更多、功能更复杂的函数去调用它
	// 这样写不体现底层驱动顶层
	//string& string::operator+=(const char* str)
	//{
	//	size_t len = strlen(str);
	//	if (_size + len > _capacity)
	//		reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
	//	strcpy(_str + _size, str);
	//	_size += len;
	//	return (*this);
	//}

	//void string::append(const char* str)
	//{
	//	*this += str;
	//}

	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			// 大于2倍，需要多少开多少，小于2倍按2倍扩
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}

		strcpy(_str + _size, str);
		_size += len;
	}

	string& string::operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	void string::insert(size_t pos, char ch)
	{
		assert(pos < _size);
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		
		// 当pos是0的时候头插，无符号整型的end循环时从0开始减会变成整形最大值，死循环或者越界访问内存
		/*size_t end = _size;
		while (end >= pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_size++;
		_str[pos] = ch;*/

		// 一:强制类型转换
		/*int end = _size;
		while (end >= (int)pos)
		{
			_str[end + 1] = _str[end];
			end--;
		}
		_size++;
		_str[pos] = ch;*/

		// 二 :尽量使用大小于号和无符号整形，保持风格
		size_t end = _size + 1;	// end指向\0的下一个位置
		//挪动数据
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			end--;
		}
		_size++;
		_str[pos] = ch;
	}
	
	void string::insert(size_t pos, const char* str)
	{
		assert(pos < _size);
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			// 大于2倍，需要多少开多少，小于2倍按2倍扩
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		size_t end = _size + len;
		// 挪动数据
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			end--;
		}
		_size += len;
		for (int i = 0; i < len; i++)
		{
			_str[pos + i] = str[i];
		}
	}

}