#ifndef _DATE
 #define _DATE

#include <iostream>

using namespace std;


class Date{
  string weekDay;
  unsigned int hour;
  unsigned int minutes;
 public:
  Date(string day, unsigned int hour, unsigned int minutes);
};

#endif
