#pragma once
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <string>
namespace xjw
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		
		// C++11新支持的默认构造函数写法
		vector() = default;

		// 类模板里面的成员函数，依旧可以是函数模板，而且用任意迭代器区间构造
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			// 不是所有的迭代器都有大小于号的比较，需要用不等于
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(int n, T val = T())
		{
			reserve(n);
			for (int i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// 这个构造会与迭代器构造起冲突，需要提供int的n的构造
		vector(size_t n, T val = T())
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				push_back(val);
			}
		}

		// 析构函数
		~vector()
		{
			if (_start)
			{
				delete[] _start;
				_start = _finish = _end_of_storage = nullptr;
			}
		}

		// 拷贝构造函数
		vector(const vector<T>& v)
		{
			reserve(v.size());
			for (auto& e : v)
			{
				push_back(e);
			}
		}

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

		//普通写法
		/*vector<T>& operator=(const vector<T>& v)
		{
			if (*this != v)
			{
				clear();
				reserve(v.size());
				for (auto e : v)
				{
					push_back(e);
				}
			}
			return *this;
		}*/

		//现代写法
		//参数不引用，构造一个临时对象交换，临时对象出作用域就销毁了
		//类模板的成员函数可以省略参数
		//vector& operator=(const vector v)
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}

		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}

		void clear()
		{
			_finish = _start;
		}

		void reserve(size_t n)		// 扩容
		{
			if (n > capacity())
			{
				size_t old_size = size();
				T* tmp = new T[n];
				// 不能使用memcpy，如果对象是自定义的类型会造成浅拷贝，释放旧空间变成野指针
				//memcpy(tmp, _start, sizeof(T) * old_size);
				for (size_t i = 0; i < old_size; i++)
				{
					tmp[i] = _start[i];
				}
				delete[] _start;
				_start = tmp;
				_finish = tmp + old_size;
				_end_of_storage = tmp + n;
			}
		}

		bool empty()		// 判空
		{
			return _start == _finish;
		}

		void push_back(const T& x)		// 尾插
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

		iterator insert(iterator pos, const T& x)		// pos位置之前插入
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

		//删除之后可能会迭代器失效，需要更新
		iterator erase(iterator pos)		// 删除数据
		{
			assert(pos >= _start);
			assert(pos < _finish);
			iterator it = pos + 1;
			while (it != end())
			{
				*(it - 1) = *(it);
				++it;
			}
			--_finish;
			return pos;
		}

		void resize(int n, T val = T())		// 调整数据容量
		{
			if (n < size())
				_finish = _start + n;
			else
			{
				reserve(n);
				while (_finish < _start + n)
				{
					*(_finish) = val;
					++_finish;
				}
			}
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

	template<class Container>
	void container_print(Container& v)
	{
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
		p = v1.insert(p, 15);
		// 如果扩容，这个p的指针可能会变成野指针，会对别的地方进行修改，也是失效
		// 要更新指针
		*(p + 1) *= 100;
		//vector_print(v1);
	}

	void my_vector_test02()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int>::iterator it = v1.begin();
		while (it != v1.end())
		{
			if (*it % 2 == 0)
				it = v1.erase(it);
			else
				++it;
		}
		container_print(v1);
	}

	void my_vector_test03()
	{
		vector<int> v1;
		v1.resize(10, 1);
		container_print(v1);
		v1.resize(15, 2);
		container_print(v1);
		v1.resize(5, 3);
		container_print(v1);
	}

	void my_vector_test04()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2;
		v2 = v1;
		container_print(v1);
		container_print(v2);
	}

	void my_vector_test05()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		vector<int> v2(v1.begin(), v1.end());
		container_print(v1);
		container_print(v2);


		// 这个构造在n个数值和迭代器区间构造中选择，需要注意
		vector<int> v3(10, 1);
		container_print(v3);

	}

	void my_vector_test06()
	{
		// 对象是自定义类型时mamcpy指挥单纯的移动数据，会造成野指针
		vector<string> v1;
		v1.push_back("111111111111111");
		v1.push_back("111111111111111");
		v1.push_back("111111111111111");
		v1.push_back("111111111111111");
		container_print(v1);
		v1.push_back("111111111111111");
		container_print(v1);
	}
}