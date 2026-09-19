#include "mymap.h"
#include "myset.h"
int main()
{
	xjw::set<int> s1;
	s1.insert(1);
	s1.insert(5);
	s1.insert(2);
	s1.insert(6);
	s1.insert(8);
	s1.insert(9);
	s1.insert(3);

	for (auto e : s1)
	{
		cout << e << " ";
	}
	cout << endl;

	xjw::map<string, string> dict;
	dict.insert({ "sort", "ÅÅĞò" });
	dict.insert({ "left", "×ó±ß" });
	dict.insert({ "right", "ÓÒ±ß" });

	

	xjw::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		// ²»ÄÜĞŞ¸Äfirst£¬¿ÉÒÔĞŞ¸Äsecond
		//it->first += 'x';
		it->second += 'x';

		cout << it->first << ":" << it->second << endl;
		++it;
	}
	cout << endl;

	dict["left"] = "×ó±ß£¬Ê£Óà";
	dict["insert"] = "²åÈë";
	dict["string"];

	for (auto& kv : dict)
	{
		cout << kv.first << ":" << kv.second << endl;
	}

	return 0;
}