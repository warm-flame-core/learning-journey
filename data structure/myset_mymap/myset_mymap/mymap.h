#pragma once
#include"RBTree.h"
namespace xjw
{
	template<class K,class V>
	class map
	{
	public:

	private:
		RBTree<K, pair<K, V>> _t;
	};
}
