#pragma once
#include <vector>
using namespace std;


//标识节点的属性，占、空、删
enum State
{
	EXIST,
	EMPTY,
	DELETE
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
private:
	vector<HashData<K, V>> _tables;
	size_t _n = 0;  // 表中存储数据个数

};