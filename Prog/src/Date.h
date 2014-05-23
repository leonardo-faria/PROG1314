#ifndef _DATE
#define _DATE

//#include <iostream>
#include <string>
#include <vector>

using namespace std;
template<class T>
int member(vector<T> v, T e);

class Date {
	string weekDay;
	unsigned int hour;
	unsigned int minutes;
	static vector<string> week;
public:
	static vector<string> getWeek();
	static Date currentDate();
	static void init();
	Date(){};
	Date(string day, unsigned int hour, unsigned int minutes);

	const string& getWeekDay() const {
		return weekDay;
	}

	const bool operator<(const Date d) const {
			if (member(week, weekDay) < member(week, d.weekDay))
				return true;
			if (hour < d.hour)
				return true;
			if (minutes < d.minutes)
				return true;
			return false;
		}
	const bool operator>(const Date d) const {
			if (member(week, weekDay) > member(week, d.weekDay))
				return true;
			if (hour > d.hour)
				return true;
			if (minutes > d.minutes)
				return true;
			return false;
		}

	void operator=(const Date &d)
	{
		this->hour=d.hour;
		this->minutes=d.minutes;
		this->weekDay=d.weekDay;
	}


	const Date operator+(const int &d) const {
		string day = weekDay;
		if ((hour + (d % 60)) % 24 >= 0) {
			for (int i = 0; i < week.size(); ++i) {
				if (weekDay == week[i] && i < week.size() - 1) {
					day = week[i + 1];
					break;
				}
			}
		}
		return Date(day, hour + (d % 60), minutes + d);
	}

	unsigned int getHour() const {
		return hour;
	}

	unsigned int getMinutes() const {
		return minutes;
	}
};

#endif
