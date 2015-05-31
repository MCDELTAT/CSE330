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
//insertion sort
int insertion_sort(vector<int>&c){
	int i;
	int j;
	int elem;
	for (i = 1; i < n; i++){
		for (elem = c[i], j = i-1; j >=0 && elem < c[j]; j--){
			c[j+1] = c[j];
		}
		c[j+1] = elem;
	}
}

//Random Number Generator
vector <int> gen_random(int a){
	int n = a;
	vector <int> v;//initialize vector
	srand(time(NULL));//seed random with time
	for (int i =0; i <= n; i++){
        int b = rand() %1000000 + 1;//set data range from 1-1000000
        v.push_back(b);//pushes onto vector
    }
	return v;
}


int main(){
	cout << "Where the numbers at?" << endl;//ask user for number of data values
	cin >> n;
	vector<int> c = gen_random(n);//create random vector
	insertion_sort(c);//run algorithm on vector

	return 0;
}