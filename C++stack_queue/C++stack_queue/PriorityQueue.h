#pragma once
#include <vector>
namespace xjw
{
	template<class T, class Container = vector<T>>
	class priority_queue
	{
	public:
		// 入堆需要向上调整
		void adjustup(int child)
		{
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (_con[parent] < _con[child])
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
			// 假设法，先假设左边孩子更大
			size_t child = parent * 2 + 1;
			// 孩子序号小于个数说明已经是叶子节点了
			while (child < _con.size())
			{
				// 有可能右边孩子更大
				if (child + 1 < _con.size() && _con[child] < _con[child + 1])
					++child;
				if (_con[parent] < _con[child])
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
			_con.pop.back();
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