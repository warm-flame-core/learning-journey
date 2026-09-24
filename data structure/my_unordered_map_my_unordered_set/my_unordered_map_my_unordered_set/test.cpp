#include "my_unordered_set.h"
#include "my_unordered_map.h"
int main()
{
	xjw::unordered_set<int> s1;
	s1.insert(1);
	xjw::unordered_map<int, int> ht1;
	ht1.insert({ 1,1 });
	return 0;
}