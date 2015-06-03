#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;	

//apply the sieve of Eratosthenes to remove all non-prime
//numbers from the integer set s = { 2, 3, 4, ... n}
void sieve(vector<int>& v, int n){
	int m, i;

	//erase any previous values in s
	while (! v.empty()){
		v.pop_back();
	}

	//load the set with integers 2, 3,....n
	for (m = 2; m < n; m++){
		v.push_back(m);
	}
	//find the primes using the Sieve of Eratosthenes
	//look at all numbers from m=2 to m*m > n (n <= sqrt(n))
	bool isInVector = false;
	for (m = 2; m*m <= n; m++){
		//check if m is still in the set, if so remove all higher
		//multiples of m starting with j = 2*m.

		for (int j = 2; j < v.size(); j++){
			int * p;
			isInVector = find(v.begin(), v.end(), m)!=v.end();
			if (isInVector){
				i = 2 * m; //i is successive multiples of m
				while (i <= n){
					vector<int>::iterator it;
					for (it = v.begin(); it <= v.end(); it++){
						if (*it == i){
							break;
						}
					}	
				v.erase(it);
				i += m; //update i to the next multiple of m	
				}
			}
		}
	}
}

int main(){
	//set to hold the prime numbers
	vector<int> primeSet;

	//used to output the final set of primes 10 numbers per line
	vector<int>::iterator iter;
	int primeLimit, count = 0;

	cout << "Enter upper limit for the set of primes: ";
	cin >> primeLimit;
	//use the sieve of Eratosthenes to remove the non-primes
	sieve(primeSet, primeLimit);

	//use iterator to scan the resulting set, output
	//10 elements per line
	iter = primeSet.begin();
	while (iter != primeSet.end()){
		count ++;
		cout << setw(5) << *iter;
		if (count % 10 == 0)
			cout << endl;
		iter++;
	}
	cout << endl;

	return 0;
}

