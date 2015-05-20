// Class: CSE 330
// Term: Spring 2015
// Instructor: George M. Georgiou
// Name(s): Aaron Chamberlain & Richard Morones
// Lab 4
// Title: Time Complexity
// Description: This program takes an integer N as user input and generates
// a vector of N random values, then sorts them.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

int n;

//selection sort
int selection_sort(vector<int>&a){
	int i;
	int j;
	for (i = 0; i < n-1; i++){
		for (j = i+1; j < n; j++){
			if (a[i] > a[j]){
				swap(a[i], a[j]);
			}
		}
	}
}
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
	//vector<int> a = gen_random(n);
	//vector<int> b = gen_random(n);
	vector<int> c = gen_random(n);
	//selection_sort(c);
	bubble_sort(c);
	//insertion_sort(c);

	return 0;
}
