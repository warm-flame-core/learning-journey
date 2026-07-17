#pragma once
#include <vector>
namespace xjw
{
	// 本质是一个类，重载operator()
	//小于用less，大于用greater
	// 仿函数也可以偏特化，但是官方库里的仿函数没有特化
	template<class T>
	struct Less
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};
	template<class T>
	struct Less<T*>
	{
		bool operator()(T* const& x, T* const& y)
		{
			return *x < *y;
		}
	};

	template<class T>
	struct Greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	//默认是大堆，因为堆排序后小于号应该是升序
	template<class T, class Container = vector<T>, class compare = Less<T>>
	class priority_queue
	{
	public:
		// 入堆需要向上调整
		void adjustup(int child)
		{
			compare com;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				// if (_con[parent] < _con[child])
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& x)
		{
			_con.push_back(x);
			adjustup(_con.size() - 1);
		}

		// 向下调整法
		void adjustdown(int parent)
		{
			compare com;
			// 假设法，先假设左边孩子更大
			int child = parent * 2 + 1;
			// 孩子序号小于个数说明已经是叶子节点了
			while (child < _con.size())
			{
				// 有可能右边孩子更大
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
					++child;
				//if (_con[parent] < _con[child])
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjustdown(0);
		}
		const T& top()
		{
			return _con[0];
		}

		size_t size() const
		{
			return _con.size();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Container _con;
	};
}