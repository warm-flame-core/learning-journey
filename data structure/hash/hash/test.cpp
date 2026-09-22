#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<set>
#include<unordered_set>

using namespace std;

void test_set1()
{
	unordered_set<int> s = { 3,1,6,7,8,2,1,1,5,6,7,6 };
	unordered_set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_set2()
{
	const size_t N = 10000000;
	unordered_set<int> us;
	set<int> s;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; ++i)
	{
		//v.push_back(rand()); // N比较大时，重复值比较多
		//v.push_back(rand() + i); // 重复值相对少
		v.push_back(i); // 没有重复，有序
	}

	size_t begin1 = clock();
	for (auto e : v)
	{
		s.insert(e);
	}
	size_t end1 = clock();
	cout << "set insert:" << end1 - begin1 << endl;

	size_t begin2 = clock();
	us.reserve(N);
	for (auto e : v)
	{
		us.insert(e);
	}
	size_t end2 = clock();
	cout << "unordered_set insert:" << end2 - begin2 << endl;

	cout << "插入数据个数：" << s.size() << endl;
	cout << "插入数据个数：" << us.size() << endl << endl;

	int m1 = 0;
	size_t begin3 = clock();
	for (auto e : v)
	{
		auto ret = s.find(e);
		if (ret != s.end())
		{
			++m1;
		}
	}
	size_t end3 = clock();
	cout << "set find:" << end3 - begin3 << "->" << m1 << endl;

	int m2 = 0;
	size_t begin4 = clock();
	for (auto e : v)
	{
		auto ret = us.find(e);
		if (ret != us.end())
		{
			++m2;
		}
	}
	size_t end4 = clock();
	cout << "unorered_set find:" << end4 - begin4 << "->" << m2 << endl;

	size_t begin5 = clock();
	for (auto e : v)
	{
		s.erase(e);
	}
	size_t end5 = clock();
	cout << "set erase:" << end5 - begin5 << endl;
	size_t begin6 = clock();

	for (auto e : v)
	{
		us.erase(e);
	}
	size_t end6 = clock();
	cout << "unordered_set erase:" << end6 - begin6 << endl << endl;
}

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Hash.h"
#include <string>
void test_hash1()
{
	int a[] = { 19,30,5,36,13,20,21,12 };
	open_address::HashTable<int, int> ht;
	for (auto e : a)
	{
		ht.Insert({ e, e });
	}

	ht.Insert({ 15,15 });
}

void test_hash2()
{
	int a[] = { 19,30,5,36,13,20,21,12 };
	hash_bucket::HashTable<int, int> ht;
	for (auto e : a)
	{
		ht.Insert({ e, e });
	}

	ht.Insert({ 15,15 });

	hash_bucket::HashTable<string, int> ht2;
	ht2.Insert({ "left",1 });
	ht2.Insert({ "right",2 });
	ht2.Insert({ "sort",6 });
	ht2.Insert({ "stop",8 });
	cout << ht2.Erase("left") << endl;

}


// AI生成的测试函数
void TestHashBucket()
{
	hash_bucket::HashTable<string, int> ht;

	// 1. 测试 Insert
	cout << "===== 测试 Insert =====" << endl;
	cout << ht.Insert({ "apple", 1 }) << endl;    // 1
	cout << ht.Insert({ "banana", 2 }) << endl;   // 1
	cout << ht.Insert({ "cherry", 3 }) << endl;   // 1
	cout << ht.Insert({ "apple", 10 }) << endl;   // 0，重复插入
	cout << ht.Insert({ "dog", 4 }) << endl;      // 1
	cout << ht.Insert({ "elephant", 5 }) << endl; // 1

	// 2. 测试 Find
	cout << "===== 测试 Find =====" << endl;
	auto ret1 = ht.Find("apple");
	if (ret1)
		cout << "apple: " << ret1->_kv.second << endl;  // 1
	else
		cout << "apple not found" << endl;

	auto ret2 = ht.Find("banana");
	if (ret2)
		cout << "banana: " << ret2->_kv.second << endl;  // 2
	else
		cout << "banana not found" << endl;

	auto ret3 = ht.Find("xxx");
	if (ret3)
		cout << "xxx: " << ret3->_kv.second << endl;
	else
		cout << "xxx not found" << endl;  // 走这里

	// 3. 测试 Erase
	cout << "===== 测试 Erase =====" << endl;
	cout << "erase apple: " << ht.Erase("apple") << endl;    // 1
	cout << "erase apple: " << ht.Erase("apple") << endl;    // 0，已删除
	cout << "erase xxx: " << ht.Erase("xxx") << endl;        // 0，不存在

	auto ret4 = ht.Find("apple");
	if (ret4)
		cout << "apple still exists" << endl;
	else
		cout << "apple deleted" << endl;  // 走这里

	// 4. 测试扩容（插入大量数据触发）
	cout << "===== 测试扩容 =====" << endl;
	for (int i = 0; i < 100; i++)
	{
		ht.Insert({ to_string(i), i });
	}
	// 验证部分数据
	for (int i = 0; i < 100; i++)
	{
		auto ret = ht.Find(to_string(i));
		if (!ret || ret->_kv.second != i)
		{
			cout << "扩容后数据错误: " << i << endl;
			return;
		}
	}
	cout << "扩容测试通过" << endl;

	// 5. 测试拷贝构造函数
	cout << "===== 测试拷贝构造 =====" << endl;
	hash_bucket::HashTable<string, int> ht2(ht);
	auto ret5 = ht2.Find("banana");
	if (ret5)
		cout << "ht2 banana: " << ret5->_kv.second << endl;  // 2
	else
		cout << "ht2 banana not found" << endl;

	// 深拷贝验证：修改 ht 不影响 ht2
	ht.Erase("banana");
	auto ret6 = ht2.Find("banana");
	if (ret6)
		cout << "深拷贝验证通过：ht2 不受 ht 影响" << endl;
	else
		cout << "深拷贝验证失败" << endl;

	// 6. 测试拷贝赋值运算符
	cout << "===== 测试拷贝赋值 =====" << endl;
	hash_bucket::HashTable<string, int> ht3;
	ht3.Insert({ "temp", 999 });
	ht3 = ht2;  // 调用 operator=
	auto ret7 = ht3.Find("dog");
	if (ret7)
		cout << "ht3 dog: " << ret7->_kv.second << endl;  // 4
	else
		cout << "ht3 dog not found" << endl;

	// 7. 测试自赋值
	cout << "===== 测试自赋值 =====" << endl;
	ht3 = ht3;
	auto ret8 = ht3.Find("dog");
	if (ret8)
		cout << "自赋值后 dog: " << ret8->_kv.second << endl;  // 4
	else
		cout << "自赋值后 dog not found" << endl;

	cout << "===== 所有测试完成 =====" << endl;
}


int main()
{
	//test_set1();
	//test_set2();

	//test_hash2();
	TestHashBucket();

	_CrtDumpMemoryLeaks();
	return 0;
}