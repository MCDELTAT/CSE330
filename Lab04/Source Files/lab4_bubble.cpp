// Class: CSE 330
// Term: Spring 2015
// Instructor: George M. Georgiou
// Name(s): Aaron Chamberlain & Richard Morones
// Lab 4
// Title:: Time Complexity

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

int n;
//bubble sort
int bubble_sort(vector<int> &b){
	int i;
	int j;
	for (i = n-1; i > 0; i--){
		for (j = 0; j < i; j++){
			if (b[j] > b[j+1]){
				swap(b[j], b[j+1]);
			}
		}
	}
}
vector <int> gen_random(int a){
	int n = a;
	vector <int> v;
	srand(time(NULL));   
	for (int i =0; i <= n; i++){
        int b = rand() %1000000 + 1;
        v.push_back(b);
    }
	return v;
}
int main(){
	cout << "Where the numbers at?" << endl;
	cin >> n;
	vector<int> b = gen_random(n);
	bubble_sort(b);
	return 0;
}