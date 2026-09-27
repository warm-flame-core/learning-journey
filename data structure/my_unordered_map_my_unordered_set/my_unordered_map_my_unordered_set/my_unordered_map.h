#pragma once
#include "Hash.h"
namespace xjw
{
	template<class K,class V>
	class unordered_map
	{
	public:
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv) const
			{
				return kv.first;
			}
		};
		typedef typename hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT>::Iterator iterator;


		iterator begin()
		{
			return _ht.Begin();
		}
		iterator end()
		{
			return _ht.End();
		}
		
		bool insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
	private:
		hash_bucket::HashTable<K, pair<K,V>, MapKeyOfT> _ht;
	};
}