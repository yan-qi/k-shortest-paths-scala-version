/************************************************************************/
/* $Id$                                                                 */
/************************************************************************/

#include <iostream>
#include <set>
#include <map>
using namespace std;

map<int, set<int> > tmp_map;

void test()
{
	set<int> tmp_set; 
	tmp_set.insert(1);
	tmp_set.insert(2);
	tmp_set.insert(3);

	tmp_map.insert(make_pair(1,tmp_set));	
}



int main(...)
{
	cout << "Welcome to the real world!" << endl;
	test();
	for (map<int, set<int> >::iterator iter = tmp_map.begin(); iter !=
		tmp_map.end(); iter++)
	{
		cout << (*iter).second.size() << endl;
	}
}
