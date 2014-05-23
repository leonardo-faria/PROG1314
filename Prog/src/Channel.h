#ifndef _CHANNEL
#define _CHANNEL

#include<iostream>
#include<vector>
#include<string>

#include "Program.h"

using namespace std;

class Channel {
	string name;
	vector<Program> programs;
public:
	Channel(string name);

	const string& getName() const {
		return name;
	}

	const vector<Program>& getPrograms() const {
		return programs;
	}

	void setName(const string& name) {
		this->name = name;
	}
};

#endif
