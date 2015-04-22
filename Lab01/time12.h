#include <iostream>
#include <iomanip>

//maintains clock time
class time12{
	private:
		int hour, minute;
		bool timeUnit;
	public:
		time12(int h=12, int m=0, bool tunit=0);
			//initialize time24 data member t
		void normalizeTime();

		void addTime(int m);
			//add m minutes to update current time

		void readTime();

		void writeTime();
			//IO member functions use format HH:MM: AM (PM)					
};


//Class Implementation//
//Constructor
time12::time12(int h, int m, bool tunit) : hour(h), minute(m), timeUnit(tunit)
{

}

void time12::normalizeTime()
{
	
	int extraHours = minute / 60;
	minute %= 60;

	int addedTime= (hour + extraHours);
   	if (addedTime >= 12 && timeUnit == 0){
   		timeUnit = 1;
   	}
   	else if(addedTime >= 12 && timeUnit == 1){
   		timeUnit = 0;
   	}

	hour = addedTime % 12;
	if (hour==0){
		hour += 12;
	}
}

//Add Time
void time12::addTime(int m){
	minute += m;
	normalizeTime();
}

//Input Time
void time12::readTime(){

}

//Output Time
void time12::writeTime(){
	std::cout << hour << ':';
   	//Output minute
   	std::cout << minute << "  ";
   	//Output Time Unit
   	if (timeUnit == 0){
   		std::cout << "AM" << "\n";
   	}
   	if (timeUnit == 1){
   		std::cout << "PM" << "\n";
   	}
}

/* 
Example: 
time12 t(8,15, AM);

t.writeTime(); 		//Output: 8:15 AM
t.readTIme();		//Input: 12:00 PM
t.addTime(180);		//add 3hours to t
t.writeTime();		//Output: 3:00 PM
*/