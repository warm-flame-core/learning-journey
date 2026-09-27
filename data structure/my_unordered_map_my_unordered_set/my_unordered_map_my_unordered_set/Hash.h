#pragma once
#include <vector>
#include <utility>
#include <string>




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




namespace hash_bucket
{
	// 一些声明
	template<class K, class T, class KeyOfT, class Hash>
	class HashTable;

	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{
		}
	};

	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash = HashFunc<K>>
	struct HTIterator
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, KeyOfT, Hash> HT;
		typedef HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		HTIterator(Node* node, HT* ht)
			:_node(node)
			, _ht(ht)
		{
		}

		Ref operator*()
		{
			return _node->_data;
		}
		Ptr operator->()
		{
			return &_node->_data;
		}

		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

		Self& operator++()
		{
			// 节点下一个不为空,++到下一个节点
			if (_node->_next)
				_node = _node->_next;
			// 当前捅走完，找下一个非空桶
			else
			{
				KeyOfT kot;
				Hash hash;
				size_t hashi = hash(kot(_node->_data)) % _ht->_tables.size();
				++hashi;
				while (hashi < _ht->_tables.size())
				{
					_node = _ht->_tables[hashi];
					if (_node)
						break;
					else
						++hashi;
				}
				// 所有桶走完了，返回空
				if (hashi == _ht->_tables.size())
				{
					_node = nullptr;
				}
			}
			// return { _node,this };
			return *this;
		}

		Node* _node;
		HT* _ht;
	};

	template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
	class HashTable
	{
		// 模板的友元需要带上模板参数，因为迭代器和捅相互依赖
		template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
		friend struct HTIterator;

		typedef HashNode<T> Node;
	public:
		typedef HTIterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef HTIterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;
		Iterator Begin()
		{
			// 桶时空的就不要遍历了
			if (_n == 0)
				return End();

			// 找第一个非空桶
			for (size_t i = 0;i < _tables.size();i++)
			{
				Node* cur = _tables[i];
				if (cur)
					return { cur,this };
			}
			return End();
		}

		Iterator End()
		{
			return { nullptr,this };
		}

		Iterator Begin() const
		{
			// 桶时空的就不要遍历了
			if (_n == 0)
				return End();

			// 找第一个非空桶
			for (size_t i = 0;i < _tables.size();i++)
			{
				Node* cur = _tables[i];
				if (cur)
					return { cur,this };
			}
			return End();
		}

		Iterator End() const
		{
			return { nullptr,this };
		}

		HashTable()
			:_tables(__stl_next_prime(0))
			//:_tables(11)
			, _n(0)
		{
		}

		~HashTable()
		{
			for (int i = 0;i < _tables.size();i++)
			{
				Node* cur = _tables[i];
				Node* next = nullptr;
				while (cur)
				{
					next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
			_n = 0;
		}

		HashTable(const HashTable<K, T, KeyOfT, Hash>& ht)
			:_tables(ht._tables.size())
			, _n(ht._n)
		{
			for (int i = 0;i < ht._tables.size();i++)
			{
				Node* cur = ht._tables[i];
				while (cur)
				{
					Insert(cur->_kv);
					cur = cur->_next;
				}
			}
		}

		HashTable<K, T, KeyOfT, Hash>& operator=(HashTable<K, T, KeyOfT, Hash> ht)
		{
			swap(_tables, ht._tables);
			swap(_n, ht._n);
			return *this;
		}


		bool Insert(const T& data)
		{
			Hash hash;
			KeyOfT kot;
			// 不允许冗余
			if (Find(kot(data)))
				return false;




			// 扩容，链地址法大于1扩容
			if (_n > _tables.size())
			{


				// 这样写效率很低，因为现在vector是挂节点，复用插入逻辑是先销毁再创建节点，效率低下
				/*HashTable<K, V> newht;
				newht._tables.resize(__stl_next_prime(_tables.size() + 1));
				for (int i = 0;i < _tables.size();i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						newht.Insert(cur);
						cur = cur->_next;
					}
				}
				_tables.swap(newht._tables);
				_n = newht._n;*/


				//直接把节点拿下来会更好
				//vector<Node*> newTables((_tables.size() * 2));	//测试的时候换2倍很好测试



				vector<Node*> newTables(__stl_next_prime(_tables.size() + 1));
				for (int i = 0;i < _tables.size();i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						size_t hashi = hash(kot(cur->_data)) % newTables.size();
						// 头插
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newTables);
			}



			size_t hashi = hash(kot(data)) % _tables.size();
			// 头插
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return true;
		}


		Node* Find(const K& key)
		{
			Hash hash;
			KeyOfT kot;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
					return cur;
				cur = cur->_next;
			}
			return nullptr;
		}


		bool Erase(const K& key)
		{
			KeyOfT kot;
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					// 头节点
					if (_tables[hashi] == cur)
					{
						_tables[hashi] = cur->_next;
					}
					// 中间节点
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_n;
					return true;
				}

				//继续往下找
				prev = cur;
				cur = cur->_next;

			}
			return false;
		}

	private:
		vector<Node*> _tables;
		size_t _n;
	};
}