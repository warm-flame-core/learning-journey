#pragma once
#include <vector>
#include <utility>
using namespace std;

// 仿照stl库设置素数表
inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}


//标识节点的属性，占、空、删
enum State
{
	EXIST,	// 已有
	EMPTY,	// 空
	DELETE	// 删除
};
template<class K, class V>
struct HashData
{
	pair<K, V> _kv;
	State _state = EMPTY;
};

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 模板偏特化，对于常见比较类型使用偏特化可以少传一个参数
template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		// BKDR算法，字符串哈希函数
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
			hash *= 131;
		}

		return hash;
	}
};



template<class K, class V,class Hash = HashFunc<K>>
class HashTable
{
public:
	HashTable()
		//:_tables(11)
		:_tables(__stl_next_prime(0))
		,_n(0)
	{}

	bool Insert(const pair<K, V>& kv)
	{
		// 不允许冗余
		if (Find(kv.first))
			return false;



		// 对于开放定址法和线性探测需要保持负债因子比较低
		// 负载因子 <= 0.7
		if (_n * 10 / _tables.size() >= 7)
		{
			// 扩容
			// 
			// 
			// 
			// 这种写法不好，要多写一份选址方法，可以直接复用
			//vector<HashData<K, V>> newtables(_tables.size() * 2);
			//for (auto& data : _tables)
			//{
			//	if (data._state == EXIST)
			//	{
			//		// 重新选址
			//	}
			//}
			//_tables.swap(newtables);

			HashTable<K, V> newht;
			//newht._tables.resize(_tables.size() * 2);
			newht._tables.resize(__stl_next_prime(_tables.size() + 1));
			for (auto& data : _tables)
			{
				if (data._state == EXIST)
				{
					newht.Insert(data._kv);
				}
			}
			_tables.swap(newht._tables);
			_n = newht._n;
		}
		

		Hash hash;
		// 必须用size取模，不能确保capacity全部都用上，用capacity会造成越界
		size_t hash0 = hash(kv.first) % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;
		while (_tables[hashi]._state == EXIST)
		{
			// 线性探测法
			hashi = (hash0 + i) % _tables.size();	// 如果当前位置被占了那就走下一个，但是为了确保不越界每次都取模
			++i;


			// 二次探测法
			/*hashi = (hash0 + (i*i*flag)) % _tables.size();
				if (hashi < _tables.size())
					hashi += _tables.size();

				if (flag == 1)
				{
					flag = -1;
				}
				else
				{
					++i;
					flag = 1;
				}*/
		}
		// 走到这里一定是找到了可以放的位置
		_tables[hashi]._kv = kv;
		_tables[hashi]._state = EXIST;
		++_n;
		return true;
	}


	HashData<K, V>* Find(const K& key)
	{
		Hash hash;
		size_t hash0 = hash(key) % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;
		while (_tables[hashi]._state != EMPTY)
		{
			if (_tables[hashi]._state == EXIST && _tables[hashi]._kv.first == key)
			{
				return &_tables[hashi];
			}
			// 线性探测法
			hashi = (hash0 + i) % _tables.size();	// 如果当前位置被占了那就走下一个，但是为了确保不越界每次都取模
			++i;
		}
		return nullptr;
	}

	bool Erase(const K& key)
	{
		HashData<K, V>* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--_n;
			return true;
		}
		else
		{
			return false;
		}
	}


private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0;  // 表中存储数据个数
};