#include <iostream>
#include <map>
#include <set>
using namespace std;
//int main()
//{
//	// 去重
//	//set<int> s;
//	set<int, greater<int>> s;
//	s.insert(5);
//	s.insert(2);
//	s.insert(7);
//	s.insert(5);
//	s.insert(7);
//	s.insert(3);
//
//	//set<int>::iterator it = s.begin();
//	auto it = s.begin();
//	while (it != s.end())
//	{
//		// error C3892: “it”: 不能给常量赋值
//		//*it = 1;
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	s.insert({ 2,8,3,9,2 });
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	// void insert (initializer_list<value_type> il);
//	set<string> strset = { "sort", "insert", "add" };
//	//set<string> strset({ "sort", "insert", "add" });
//	// 
//	// 遍历string比较ascll码大小顺序遍历的
//	for (auto& e : strset)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	return 0;
//}


//int main()
//{
//	set<int> s = { 4,2,7,2,8,5,9 };
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	// 删除函数传入值时
//	// 删除最小值
//	/*s.erase(s.begin());
//	for (auto e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;*/
//
//	//// 直接删除x
//	//int x;
//	///*cin >> x;
//	//int num = s.erase(x);
//	//if (num == 0)
//	//{
//	//	cout << x << "不存在！" << endl;
//	//}
//	//else
//	//{
//	//	cout << x << "删除成功！" << endl;
//	//}*/
//
//	//cin >> x;
//	//auto pos = s.find(x);
//	//if (pos != s.end())
//	//{
//	//	// pos失效
//	//	s.erase(pos);
//	//	//cout << *pos << endl;
//	//}
//	//else
//	//{
//	//	cout << x << "不存在！" << endl;
//	//}
//
//	//for (auto e : s)
//	//{
//	//	cout << e << " ";
//	//}
//	//cout << endl;
//
//	//// 算法库的查找 O(N)
//	//auto pos1 = find(s.begin(), s.end(), x);
//
//	//// set自身实现的查找 O(logN)
//	//auto pos2 = s.find(x);
//
//	//// 利用count间接实现快速查找
//	//cin >> x;
//	//if (s.count(x))
//	//{
//	//	cout << x << "在！" << endl;
//	//}
//	//else
//	//{
//	//cout << x << "不存在！" << endl;
//	//}
//
//	return 0;
//}

// lower_bound 和upper_bound找区间左闭右开
int main()
{
	std::set<int> myset;
	for (int i = 1; i < 10; i++)
		myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
	for (auto e : myset)
	{
		cout << e << " ";
	}
	cout << endl;

	// [30, 50]值
	// [25, 55]值
	 
	//// 返回 >= 30
	//auto itlow = myset.lower_bound(30);
	//// 返回 > 50
	//auto itup = myset.upper_bound(50);

	// 返回 >= 25
	auto itlow = myset.lower_bound(25);
	// 返回 > 55
	auto itup = myset.upper_bound(55);

	// 删除这段区间的值
	myset.erase(itlow, itup);
	for (auto e : myset)
	{
		cout << e << " ";
	}
	cout << endl;
}