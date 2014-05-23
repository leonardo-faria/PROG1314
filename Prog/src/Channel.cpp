#include "Channel.h"

Channel::Channel(string name) {
	this->name=name;
}


void Channel::addProgram(Program p)
{
	programs.push_back(p);
}
