#include "Program.h"

Program::Program(string name,string type, unsigned int duration,Date date) :
		exhibitionDate(date) {
	this->name = name;
	this->duration = duration;
	this->recorded=false;
	this->type=type;
	// rest of initialisations
}

