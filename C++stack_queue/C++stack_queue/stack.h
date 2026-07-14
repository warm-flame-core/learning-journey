#pragma once
#include <vector>
using namespace std;
namespace xjw
{
	template<class T, class Container = vector<T>>
	class stack
	{
	public:
		empty()
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		T top() const
		{
			return _con.back();
		}
	private:
		Container _con;
	};
}
