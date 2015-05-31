// Class: CSE 330
// Term: Spring 2015
// Instructor: George M. Georgiou
// Name(s): Aaron Chamberlain & Richard Morones
// Lab 4
// Title: Time Complexity

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
//Random Number Generator
vector <int> gen_random(int a)
{ 
	int n = a;
	vector <int> v;	
	srand(time(NULL));//seed random with time   
	for (int i =0; i <= n; i++){
        int b = rand() %1000000 + 1;//set data range (1-1000000)
        v.push_back(b);//pushes onto vector
    }
	return v;
}


int main(){
	cout << "Where the numbers at?" << endl; //ask user for number of data values
	cin >> n;
	vector<int> a = gen_random(n);//create random vector
	selection_sort(a);//run algorithm on vector
	return 0;
}