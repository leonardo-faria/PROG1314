#ifndef _DATE
#define _DATE

#include <iostream>
#include <vector>
using namespace std;

class Date {
	string weekDay;
	unsigned int hour;
	unsigned int minutes;
	static vector<string> week;
public:
	static vector<string> getWeek();
	static Date currentDate();
	static void init();
	Date(string day, unsigned int hour, unsigned int minutes);

	const string& getWeekDay() const {
		return weekDay;
	}
};

#endif
