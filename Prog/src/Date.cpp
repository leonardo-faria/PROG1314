#include "Date.h"

vector<string> Date::week;
Date::Date(string day, unsigned int hour, unsigned int minutes) {
	this->weekDay = day;
	this->hour = hour;
	this->minutes = minutes;

}

void Date::init() {
	if (week.size() == 0) {
		week.push_back("Sunday");
		week.push_back("Monday");
		week.push_back("Tuesday");
		week.push_back("Wednesday");
		week.push_back("Thursday");
		week.push_back("Friday");
		week.push_back("Saturday");
	}
}

Date Date::currentDate() {
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return Date(week[timeinfo->tm_wday], timeinfo->tm_hour, timeinfo->tm_min);
}

vector<string> Date::getWeek()
{
	return week;
}
