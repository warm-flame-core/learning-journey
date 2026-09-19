#pragma once
#include <vector>
#include <utility>
using namespace std;


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
template<class K, class V>
class HashTable
{
public:
	HashTable()
		:_tables(11)
		,_n(0)
	{}

	bool Insert(const pair<K, V>& kv)
	{
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
			newht._tables.resize(_tables.size() * 2);
			for (auto& data : _tables)
			{
				if (data._state == EXIST)
				{
					newht.Insert(data._kv);
				}
			}
			_tables.swap(newht._tables);
		}
		


		// 必须用size取模，不能确保capacity全部都用上，用capacity会造成越界
		size_t hash0 = kv.first % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;
		while (_tables[hashi]._state == EXIST)
		{
			// 线性探测法
			hashi = (hash0 + i) % _tables.size();	// 如果当前位置被占了那就走下一个，但是为了确保不越界每次都取模
			++i;
		}
		// 走到这里一定是找到了可以放的位置
		_tables[hashi]._kv = kv;
		_tables[hashi]._state = EXIST;
		++_n;
		return true;
	}


private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0;  // 表中存储数据个数
};