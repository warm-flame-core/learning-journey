#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <vector>
namespace xjw
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		size_t size() const
		{
			return _finish - _start;
		}
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		T& operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		const T& operator[](size_t i) const
		{
			assert(i < size());
			return _start[i];
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				memcpy(tmp, _start, sizeof(T) * size());
				delete[] _start;
				_start = tmp;
				_finish = tmp + old_size;
				_end_of_storage = tmp + n;
			}
		}
		bool empty()
		{
			return _start == _finish;
		}
		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = x;
			_finish++;
		}
		void pop_back()
		{
			assert(!empty());
			_finish--;
		}
		iterator insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				// 比如先算相对位置，因为扩容之后pos变成了野指针
				// 迭代器失效的一种类型
				size_t len = pos - begin();
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = begin() + len;
			}
			iterator end = _finish - 1;
			while (end > pos - 1)
			{
				*(end + 1) = *end;
				end--;
			}
			*pos = x;
			++_finish;

			// 但是使用后的pos失效了，不能再次使用，需要重新获取，迭代器失效的一种类型
			// 需要返回迭代器
			return pos;
		}
	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};


	template<class T>
	void vector_print(const vector<T>& v)
	{
		// 从未实例化的模板取类型需要明确是类型还是成员变量
		//vector<T>::const_iterator it = v.begin();
		//typename vector<T>::const_iterator it = v.begin();
		auto it = v.begin();
		while (it != v.end())
		{
			cout << *it << ' ';
		}
		cout << endl;
		for (auto e : v)
		{
			cout << e << ' ';
		}
		cout << endl;
	}





	void my_vector_test01()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		//v1.push_back(5);
		v1.pop_back();
		int x;
		cin >> x;
		auto p = find(v1.begin(), v1.end(), x);
		v1.insert(p, 15);
		// 如果扩容，这个p的指针可能会变成野指针，会对别的地方进行修改，也是失效
		// 
		*(p + 1) *= 100;
		//vector_print(v1);
	}
}