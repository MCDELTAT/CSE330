//specifies clock time units
enum timeUnit {AM, PM};

//maintains clock time
class time12{
	private:
		time24 t;
			//store time in 24-hour format
		time24 convert12To24(int h, int m, timeUnit tunit);
			//build t from standard time
	public:
		time12(int h=12, int m=0, timeUnit tunit = AM);
			//initialize time24 data member t
		void addTime(int m);
			//add m minutes to update current time

		void readTime();
		void writeTime();
			//IO member functions use format HH:MM: AM (PM)					
};

/* 
Example: 
time12 t(8,15, AM);

t.writeTime(); 		//Output: 8:15 AM
t.readTIme();		//Input: 12:00 PM
t.addTime(180);		//add 3hours to t
t.writeTime();		//Output: 3:00 PM
*/