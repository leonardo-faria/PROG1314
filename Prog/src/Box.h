#ifndef _BOX
#define _BOX

#include<iostream>
#include<vector>
#include<string>

#include "Date.h"
#include "Channel.h"
#include "Program.h"
#include "Movie.h"
#include "Menu.h"
using namespace std;

class Box {
	string password;
	Date currentDate;
	vector<Channel> channels;
	vector<Movie> movieClub;
	vector<Movie> seenMovies;
	vector<Program> recordList; // stores recorded programs and programs yet to be recorded
	//  vector<Program> recorded;    // removed in the final version of the work text

	//used for menus
	vector<string> mlogin;
	vector<string> muser;
	vector<string> madmin;
	vector<string> mlistp;
	vector<string> mdayA;
	vector<string> mdayC;
	vector<string> medit;
	vector<string> mprogram;
	vector<string> mchannel;
	vector<string> mmovie;

	void plister();
	void renter();
	void spent();
	void rented();
	void record();
	void user();
	void admin();
	void movies();
	void chans();
	void del(string name);
public:
	Box(string passwd, Date currentDate);
	vector<Program> listByDay(string day) const;
	vector<Program> listByChannel(string channel, string day) const;
	vector<Program> listByChannel(string channel) const;
	vector<Program> listByType(string type, string day) const;
	vector<Program> listByType(string type) const;

	//BOX
	int run();
};

#endif
