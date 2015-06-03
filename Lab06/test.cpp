#include "Vector.h"
#include <iostream>

using namespace std;

int main(){
	Vector <int> test(5);

	int j = 0;
	while (j<5){
		test.push_back(j);
		j++;
	}

	test.pop_back();
	test.pop_back();

	//loop through the elements to verify all were set to base value
	int i = 0;
	while (i<test.size()){
		cout << "Value at index " << i << " is: " << test[i] << ". \n";
		i++;
	}

	cout << "Size is: " << test.size() << ". \n";
	
	while (test.empty() != 1){
		cout << "Last Value in Vector is: " << test[test.size() - 1] << ". \n";
		test.pop_back();
	}

	return 0;
}