#pragma once
#include "Hash.h"
namespace xjw
{
	template<class K>
	class unordered_set
	{
	public:
		struct SetKeyOfT
		{
			const K& operator()(const K& key) const
			{
				return key;
			}
		};
		bool insert(const K& key)
		{
			return _ht.Insert(key);
		}
	private:
		hash_bucket::HashTable<K,K,SetKeyOfT> _ht;
	};
}