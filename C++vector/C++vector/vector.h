#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>
namespace xjw
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterotar;
		typedef const T* const_iterotar;
		iterotar begin()
		{
			return _start;
		}
		iterotar end()
		{
			return _finish;
		}
		const_iterotar begin() const
		{
			return _start;
		}
		const_iterotar end() const
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
		void pop_pack()
		{
			assert(!empty());
			_finish--;
		}
		void insert(iterator pos, const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			iterator end = _finish - 1;
			while (end > pos - 1)
			{
				*(end + 1) = *end;
				end--
			}
		}
	private:
		iterotar _start = nullptr;
		iterotar _finish = nullptr;
		iterotar _end_of_storage = nullptr;
	};






	void my_vector_test01()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		v1.pop_pack();
		for (auto e : v1)
		{
			cout << e << ' ';
		}
		cout << endl;
	}
}