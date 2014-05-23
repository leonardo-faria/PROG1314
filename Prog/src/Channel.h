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
	void addProgram(Program p);
	const string& getName() const {
		return name;
	}

	const vector<Program>& getPrograms() const {
		return programs;
	}

	void removePrograms(int i)
	{
		programs.erase(programs.begin()+i);
	}

	void setName(const string& name) {
		this->name = name;
	}
};

#endif
