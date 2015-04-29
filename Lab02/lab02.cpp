#include <iostream>
#include <vector>
#include <string>

/*int seqSearch(const vector<T>& v, int fist, int last, const T&  target){

}*/

int main(){
	int arr[9] = {1, 2, 6, 7, 10, 22, 19, 33, 35};
	std::cout << "Value at index 4: " << arr[4] << "\n";

	//Push array into vector
	std::vector<int> test(arr, arr+sizeof(arr)/sizeof(arr[0]));
	//test to verify the vector contains all elements
	for (std::vector<int>::iterator it = test.begin(); it != test.end(); ++it){
		std::cout << ' ' << *it;
	}
	std::cout << "\n";
	
	const int val= 10;	
	seqSearch(test, 2, 5, val);
	
	return 0;
}

template <class T>
int seqSearch(const std::vector<T>& v, int first, int last, const T& target){
	int index=0;
	
	//Declare beginning and end iterators
	std::vector<int>::iterator start = v.begin();
	std::vector<int>::iterator end = v.begin();

	//Set start iterator to value of first index
	for (int i=first; i<last; i++){
		++start;
	}

	//Set end iterator to value of last index
	for (int j=last; j<=last; j++){
		++end;
	}
	//With the pointers to the beggining and end of search field, search the vector
	for (start; start != end; ++start){
		std::cout << " " << *start;
	}
	std::cout << "\n";
	
	return 0;
	 
}
