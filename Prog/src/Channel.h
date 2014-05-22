#ifndef _CHANNEL
 #define _CHANNEL

#include<iostream>
#include<vector>
#include<string>

#include "Program.h"

using namespace std;

class Channel{
  string name;
  vector<Program> programs;
 public:
  Channel(string name);
};

#endif
