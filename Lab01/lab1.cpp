//Class: CSE330
//Term: Spring 2015
//Instructor: George M. Georgiou
//Names: Richard Morones and Aaron Chamberlain
//Lab 1
//12 Hour Time Implementation
//Description: This program uses a class time12 to create times and modify them
//all times are output in the 12 hour format with appropriate time Units(AM/PM).

#include <iostream>
#include "time12.h"

int main(){
	//First test
	time12 t(8,15, 0);	//Note: last value is a bool where 0=AM and 1=PM
	t.writeTime(); 		//Output: 8:15 AM
	t.readTime();		//Input: 12:00 PM
	t.addTime(180);		//add 3 hours
	t.writeTime();		//Output: 3:00 PM
	//second test
	std::cout << "\n" << "Second Test: \n"; //Just to differentiate
	time12 t1(8,15, 1);
	t1.writeTime(); 	//Output: 8:15 PM
	t1.readTime();		//Input: 12:00 PM
	t1.addTime(180);	//add 3 hours
	t1.writeTime();		//Output: 3:00 PM

	return 0;
}
