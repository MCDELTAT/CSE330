// Class: CSE 330
// Term: Spring 2015
// Instructor: George M. Georgiou
// Name(s): Aaron Chamberlain & Richard Morones
// Lab 8
// Title: Associatve Containers-Multiset and Multimap

#include <set>
#include <map>
#include <iostream>
#include <string>
#include <sstream> //To convert integer to string for key

using namespace std;

//declare functions
void rm_multiset_duplicates();
void rm_multimap_duplicates();

int main()
{
	//call function to construct multiset and remove duplicates
	rm_multiset_duplicates();
	cout << endl;
	//call function to construct multimap and remove duplicates
	rm_multimap_duplicates();

	return 0;
}

//function creates the multiset of values 3,4,4,5,5,6,6,7,8,9,9,10
//and then deletes the duplicates, outputing the clean multiset
void rm_multiset_duplicates()
{
	//create multiset and two iterators.
	multiset<int> m;
	multiset<int>::iterator it;
	multiset<int>::iterator it2;
	int i;
	//loop through and add values 3-10 to multiset
	for (i = 3; i<=10; i++)
	{
		m.insert(i);
		//for the numbers 4,5,6,& 9 make a duplicate entry
		if(i==4||i==5||i==6||i==9)
		{
			m.insert(i);
		}
	}
	//set position of iterators, it2 will always be 1 position ahead of it
	it = m.begin();
	it2 = m.begin();
	it2++;
	while(it2!=m.end())
	{
		//if there is a duplicate, delete the first of the two.
		if(*it == *it2)
		{
			m.erase(it);
			//it now points outside the multiset, reposition it 1 behind it2
			it = it2;
			it2++;
		}
		else //if no deletion occured, increment both to compare next two
		{
		it++;
		it2++;
		}
	}
	//dupicates are gone, verify by outputting the entire list of values
	for (it =m.begin();it !=m.end();it++)
	{
		cout << *it << endl;
	}
}

//function creates the multimap of values 3,4,4,5,5,6,6,7,8,9,9,10
//and then deletes the duplicates, outputing the clean multimap
void rm_multimap_duplicates()
{
	//create multimap and an iterator
	multimap<string, int> map;
	multimap<string, int>::iterator it;
	multimap<string, int>::iterator it2;
	int i;
	string s;
	stringstream ss;
	for(i = 3; i<=10; i++){
		//convert the value i into a string using sstream--> key
		ss.str("");
		ss << i;
		s = ss.str();
		//insert the key, data pair into map
		map.insert(pair<string,int>(s,i));
		//for values 4,5,6,& 9 place duplicate key and data pair values
		if(i==4||i==5||i==6||i==9){
			map.insert(pair<string,int>(s,i));
		}
	}
	//now with all values in vector, search for duplicates and delete
	it = map.begin();
	it2 = map.begin();
	it2++;
	while(it2!=map.end())
	{
		//if there is a duplicate, delete the first of the two.
		if(*it == *it2)
		{
			map.erase(it);
			//it now points outside the multiset, reposition it 1 behind it2
			it = it2;
			it2++;
		}
		else //if no deletion occured, increment both to compare next two
		{
		it++;
		it2++;
		}
	}
	cout << "Map contains:\n";
  	for (it=map.begin(); it!=map.end(); ++it){
	  cout << (*it).first << " => " << (*it).second << '\n';
	}
}