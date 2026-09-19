#pragma once
#include"RBTree.h"
namespace xjw
{
	template<class K>
	class set
	{
	public:
		struct SetKeyOfT
		{
			const K& operator()(const K & k)
			{
				return k;
			}
		};

		typedef typename RBTree<K,const K, SetKeyOfT>::Iterator iterator;
		typedef typename RBTree<K,const K, SetKeyOfT>::Const_Iterator const_iterator;


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


		pair<iterator, bool> insert(const K& k)
		{
			return _t.Insert(k);
		}
	private:
		// stl库里面的set对于键是不能修改的
		// 可以把第二个模板参数修改成const，但是第一个不能加
		// 查找需要用第一个接口
		//RBTree<K, K, SetKeyOfT> _t;
		RBTree<K,const K,SetKeyOfT> _t;
	};
}
