#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
int seqSearch(const vector<T>& v, int first, int last, const T& target){
	int index;
	bool isInVector = 0;
    	for(int i=first; i<=last; i++){
        	if (v[i] == target){
                	index = i;
			isInVector = 1; //Target was in vector --> TRUE.
			cout << target << " found at index " << index << endl;
                	break;
		}
	}
	//If the item wasn't in the vector isInVector still == 0
	if (isInVector == 0){
		cout << "The value " << target << " wasn't in the vector search range. \n";
		return -1;
	}
	return 0;
}

int main(){
    //Initializing arrays and strings
	int int_arr[] = {1, 2, 6, 7, 10, 22, 19, 33, 35};
	string str_arr[] = {"abs", "awp", "bhg", "sghsh", "het", "hetet"};
	string a = "het";
	string b = "abc";

	//Push array into vector
	vector <int> int_chk(int_arr, int_arr+9);
	vector <string> str_chk(str_arr, str_arr+6);

	//testing search
	cout << "Searching for 10" << endl;
	seqSearch(int_chk, 0, 8, 10);
	cout << "\n";

	cout << "Searching for 10" << endl;
	seqSearch(int_chk, 1, 6, 35);
	cout << "\n";

	cout << "Searching for " << a << endl;
	seqSearch(str_chk, 0, 5, a);
	cout << "\n";

	cout << "Searching for " << b << endl;
	seqSearch(str_chk, 1, 4, b);
	cout << "\n";
}
