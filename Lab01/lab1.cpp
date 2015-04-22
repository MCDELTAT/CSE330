#include <iostream>
#include "time12.h"

int main(){
	time12 t(11, 40, 0);
	t.writeTime();
	t.addTime(90);
	t.writeTime();
	std::cout << "\n";
	return 0;
}