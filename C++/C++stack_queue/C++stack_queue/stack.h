#pragma once
#include <vector>
#include <deque>
// 仿函数

namespace xjw
{
	// 容器适配器Container，复用已经实现好的类型
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		bool empty()
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& top() const
		{
			return _con.back();
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
	private:
		Container _con;
	};
}
