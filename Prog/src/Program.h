#ifndef _PROGRAM
 #define _PROGRAM

#include<iostream>
#include "Date.h"


using namespace std;


class Program{
  string name;
  string type;    // introduced in the final version of the work text
  bool recorded;  // introduced in the final version of the work text
  int duration;   // in minutes
  Date exhibitionDate;

 public:
  Program(string name, unsigned int duration, string day, unsigned int hour, unsigned int minutes);
};

#endif
