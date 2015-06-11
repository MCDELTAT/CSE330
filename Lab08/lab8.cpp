#include <set>
#include <map>
#include <iostream>
#include <string>
#include <sstream> //To convert integer to string for key

using namespace std;

void remove_duplicate();
void multimap_duplicates();

int main()
{
	remove_duplicate();
	cout << endl;
	multimap_duplicates();
	return 0;
}

void remove_duplicate()
{
	multiset<int> m;
	multiset<int>::iterator it;
	multiset<int>::iterator it2;
	int i;
	for (i = 3; i<=10;i++ )
	{
		m.insert(i);
		if(i ==4||i == 5||i ==6||i ==9)
		{
			m.insert(i);
		}
	}
	it = m.begin();
	it2 = m.begin();
	it2++;
	while(it2!=m.end())
	{
		if(*it == *it2)
		{
			m.erase(it);
			it = it2;
			it2++;
		}
		else
		{
		it++;
		it2++;
		}
	}
	for (it =m.begin();it !=m.end();it++)
	{
		cout << *it << endl;
	}
}

void multimap_duplicates()
{
	multimap<string, int> map;
	multimap<string, int>::iterator it;
	int i;
	string s;
	stringstream ss;
	for(i = 3; i<=10; i++){
		ss.str("");
		ss << i;
		s = ss.str();
		map.insert(pair<string,int>(s,i));
		if(i ==4||i == 5||i ==6||i ==9){
			map.insert(pair<string,int>(s,i));
		}
	}
	cout << "Map contains:\n";
  	for (it=map.begin(); it!=map.end(); ++it){
	  cout << (*it).first << " => " << (*it).second << '\n';
	}
}



