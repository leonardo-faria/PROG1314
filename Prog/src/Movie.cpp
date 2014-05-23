#include "Movie.h"

Movie::Movie(string title, float cost) {
	this->title=title;
	this->cost=cost;
	this->timesRented=0;
}
Movie::Movie(string title, float cost,int timesRented) {
	this->title=title;
	this->cost=cost;
	this->timesRented=timesRented;
}
