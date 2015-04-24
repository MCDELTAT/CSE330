#include <iostream>
#include "time12.h"

int main(){
	time12 t(8,15, 0);

	t.writeTime(); 		//Output: 8:15 AM
	t.readTime();		//Input: 12:00 PM
	t.addTime(180);		//add 3hours to t
	t.writeTime();		//Output: 3:00 PM	
	return 0;

	/* time12 t(11, 40, 0);
	t.writeTime();
	t.addTime(90);
	t.writeTime();
	std::cout << "\n";
	t.readTime();
	t.writeTime();
	std::cout << "\n";
	return 0; */
}

/* 
Example: 
*/