#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>
using namespace std;

// auto可以用于返回值但是不可以用于参数
auto func1()
{
	return 10;
}

// auto修饰，自动推导
void StringTest01()
{
	auto a = 10;
	auto b = a;
	auto c = func1();
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
}
//范围for,不引用是一种拷贝，不影响原来的值
void StringTest02()
{
	int arr[5] = { 1,2,3,4,5 };
	for (auto ch : arr)
	{
		ch++;
		cout << ch << " ";
	}
	cout << endl;
	//引用使用的时候就会修改原来的值
	for (auto &ch : arr)
	{
		ch+=2;
		cout << ch << " ";
	}


	cout << endl;
	for (auto ch : arr)
	{
		cout << ch << " ";
	}
	cout << endl;
}

// 字符串初始化的各种方法
void StringTest03()
{
	string s1;
	string s2("hello world");
	string s3(s2, 6, 5);	//从s2的索引6开始复制5个字符
	string s4(s2);
	string s5 = s4;
	string s6(s2, 6);		//从s2复制前6个字符
	string s7(6, 'c');		//6个位置都用C填充
	for (auto ch : s1)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s2)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s3)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s4)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s5)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s6)
	{
		cout << ch << " ";
	}
	cout << endl;
	for (auto ch : s7)
	{
		cout << ch << " ";
	}
	cout << endl;

}

//迭代器,循环内修改会影响原来字符串
void StringTest04()
{
	// begin类比下标0，end类比\0的下标，rbegin类比最后一个下标，rend类比与下标-1
	string s1("Hello World");
	//正向迭代器
	//string::iterator it = s1.begin();
	auto it = s1.begin();
	while (it != s1.end())
	{
		//*it += 2;
		cout << *it << " ";
		++it;
	}
	cout << endl;
	cout << endl << endl;

	//cout << endl << endl;
	//for (auto ch : s1)
	//{
	//	cout << ch << " ";
	//}
	//cout << endl;

	//反向迭代器
	//string::reverse_iterator rit = s1.rbegin();
	auto rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
	cout << endl << endl;

	const string s2 = s1;
	//const正向迭代器
	string::const_iterator cit = s2.begin();
	//auto cit = s2.begin();
	while (cit != s2.end())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
	cout << endl << endl;
	
	//const反向迭代器
	//string::const_reverse_iterator crit = s2.rbegin();
	auto crit = s2.rbegin();
	while (crit != s2.rend())
	{
		cout << *crit << " ";
		++crit;
	}
	cout << endl;
	cout << endl << endl;
}

void TestPushBack()
{
	// reverse 反转  逆置
	// reserve 保留、预留
	string s;
	// 提前开空间，避免扩容，提高效率
	//s.reserve(100);
	size_t sz = s.capacity();
	cout << "capacity changed: " << sz << '\n';

	cout << "making s grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}


//string的各种容量
void StringTest05()
{
	string s1("Hello World");
	cout << s1.size() << endl;		// 有效字符个数
	cout << s1.length() << endl;	// 有效字符个数
	cout << s1.capacity() << endl;	// 字符串有效空间
	cout << s1.empty() << endl;		// 字符串判空
	s1.reserve(15);					// 字符串扩容，但是vs对于小于16的字符串用的是buffer，开辟在栈区
	s1.resize(3);					// 字符串调整，小于有效字符个数会删除字符，可能会缩容，大于有效字符个数用\0填充
	cout << s1 << endl;
}

//string的常见函数
void StringTest06()
{
	string s1("Hello World");
	s1.append(" Hello Myself");	// 拼接字符串
	cout << s1 << endl;
	
	string s2("Hello World");	// 尾插字符
	s2.push_back('y');
	cout << s2 << endl;

	string s3("Hello World");
	s3 += ' ';					// 重载运算符拼接
	s3 += "hello world";
	cout << s3 << endl;

	string s4("Hello World");
	s4.insert(0, "1111");		// 在索引0的位置之前插入
	cout << s4 << endl;
	char ch = 't';
	s4.insert(0, 4, ch);
	cout << s4 << endl;
	s4.insert(s4.begin(), ch);	// 去迭代器开始位置插入一个t
	cout << s4 << endl;

	string s5("Hello World");	// 字符串分配新的字符
	s5.assign(4, 'c');
	cout << s5 << endl;

	string s6("Hello World");
	s6.erase(5, 1);				// 下标5的地方开始删除一个字符
	cout << s6 << endl;			// 尽量尾删除，头删效率低下
	s6.erase(s6.begin());		// 取迭代器删除
	cout << s6 << endl;

	string sss("hello                 world hello bit");
	size_t pos = sss.find(' ');
	// 这样查找字符效率低下
	/*while (pos != string::npos)
	{
		sss.replace(pos, 1, "%%");
		cout << sss << endl;

		pos = sss.find(' ', pos+2);
	}
	cout << sss << endl;*/
	
	// 用空间换时间，提前开一些空间出来
	string tmp;
	tmp.reserve(sss.size());
	for (auto ch : sss)
	{
		if (ch == ' ')
			tmp += "%%";
		else
			tmp += ch;
	}
	sss.swap(tmp);
	cout << sss << endl;

	// find:查找一个文件的文件名
	string s7("test.txt");
	int pos3 = s7.find('.');
	string filename;
	if (pos3 != string::npos) {
		// substr(0, pos) 表示从下标 0 开始，截取 pos 个长度（不包含 pos 位置的点）
		filename = s7.substr(0, pos3);
	}
	cout << filename << endl;
	
	// rfind:查找一个文件的扩展名
	string s8("test.txt.zip");
	size_t pos1 = s8.rfind('.');
	string suffix = s8.substr(pos1);
	cout << suffix << endl;

	// 将字符串中所有不是abcdef的字符换成*
	std::string str("Please, replace the vowels in this sentence by asterisks.");
	std::cout << str << '\n';
	std::size_t found = str.find_first_not_of("abcdef");
	while (found != std::string::npos)
	{
		str[found] = '*';
		found = str.find_first_not_of("abcdef", found + 1);
	}

	// c_str()：兼容C语言返回指针
	string file;
	cin >> file;
	FILE* fout = fopen(file.c_str(), "r");
	char ch1 = fgetc(fout);
	while (ch1 != EOF)
	{
		cout << ch;
		ch1 = fgetc(fout);
	}
	fclose(fout);
}

void SplitFilename(const std::string& str)
{
	std::cout << "Splitting: " << str << '\n';
	std::size_t found = str.find_last_of("/\\");

	std::cout << " path: " << str.substr(0, found) << '\n';
	std::cout << " file: " << str.substr(found + 1) << '\n';
}

void StringTest07()
{
	std::string str1("/usr/bin/man");
	std::string str2("E:\\Code\\113-issues\\24年-07月20日--string");

	SplitFilename(str1);
	SplitFilename(str2);
}

// 反转两边的字母
string reverseOnlyLetters(string s) {
	int begin = 0, end = s.size() - 1;
	while (begin < end)
	{
		while (begin < end && !isalpha(s[begin]))	// 找到左边的字母
		{
			begin++;
		}
		while (begin < end && !isalpha(s[end]))		// 找到右边的字母
		{
			end--;
		}
		swap(s[begin++], s[end--]);
	}
	return s;
}

// 返回字符串中的第一个唯一字符的索引
int firstUniqChar(string s) {
	int arr[26] = { 0 };
	for (auto ch : s)
	{
		arr[ch - 'a']++;
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (arr[s[i] - 'a'] == 1)
			return i;
	}
	return -1;
}

int main()
{
	
	//StringTest01();
	//StringTest02();
	//StringTest03();
	//StringTest04();
	//TestPushBack();
	//StringTest05();
	StringTest06();
	return 0;
}