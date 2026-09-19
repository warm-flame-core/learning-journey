#pragma once
#include"RBTree.h"
namespace xjw
{
	template<class K,class V>
	class map
	{
	public:
		

		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};

		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Const_Iterator const_iterator;


		iterator begin()
		{
			return _t.Begin();
		}

		iterator end()
		{
			return _t.End();
		}

		const_iterator begin() const
		{
			return _t.Begin();
		}

		const_iterator end()  const
		{
			return _t.End();
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);
		}


		// 下标访问复用insert
		V& operator[](const K& k)
		{
			// 如果K存在就是查找功能，如果不存在就是插入功能，值是默认值
			pair<iterator, bool> ret = insert({ k,V() });
			return ret.first->second;
		}
	private:
		// 对于map来说不能修改，所以加一个const
		//RBTree<K, pair<K, V>, MapKeyOfT> _t;
		RBTree<K, pair<const K, V>,MapKeyOfT> _t;
	};
}
