#include "Vector.h"
#include <iostream>

using namespace std;

int main(){
	Vector <int> test(5);

	//loop through the elements to verify all were set to base value
	int i = 0;
	while (i<5){
		cout << "Value at index " << i << " is: " << test[i] << ". \n";
		i++;
	}
	
	return 0;
}