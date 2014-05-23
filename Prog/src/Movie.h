#ifndef _MOVIE
#define _MOVIE

#include<iostream>

using namespace std;

class Movie {
	string title;
	//  string type; // removed in the final version of the work text
	float cost;
	unsigned timesRented;
public:
	void rent()
	{
		timesRented++;
	}

	Movie(string title, float cost);
	bool operator==(Movie& m) {
		return this->title==m.title;
	}

	float getCost() const {
		return cost;
	}

	unsigned getTimesRented() const {
		return timesRented;
	}

	const string& getTitle() const {
		return title;
	}

	void setCost(float cost) {
		this->cost = cost;
	}

	void setTimesRented(unsigned timesRented) {
		this->timesRented = timesRented;
	}

	void setTitle(const string& title) {
		this->title = title;
	}
};

#endif
