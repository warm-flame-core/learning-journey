#pragma once
#include <vector>
#include <deque>
namespace xjw
{
	template<class T, class Container = deque<T>>
	class queue
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
			return _con.front();
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
	private:
		Container _con;
	};
}
