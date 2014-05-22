#ifndef _BOX
 #define _BOX

#include<iostream>
#include<vector>
#include<string>

#include "Date.h"
#include "Channel.h"
#include "Program.h"
#include "Movie.h"

using namespace std;


class Box{
  string password;
  Date currentDate;
  vector<Channel> channels;
  vector<Movie> movieClub;
  vector<Movie> seenMovies;
  vector<Program> recordList;  // stores recorded programs and programs yet to be recorded
  //  vector<Program> recorded;    // removed in the final version of the work text

 public:
  Box(string passwd, Date currentDate);
  vector<Program> listByDay(string day) const;
  vector<Program> listByChannel(string  channel, string day) const;
  vector<Program> listByType(string  type, string day) const;
  bool rentMovies(string title);
  float moneySpent() const;
  int timesWhatched(string title) const;
  bool changePassword();          // ask, verify and change the password
  // Channel CRUD
  bool createdChanel();
  bool removeChanel();
  bool updateChanel();
  // Program CRUD
  bool createdProgram(string chanel);
  bool removeProgram();
  bool updateProgram();
  // Movie CRUD
  bool createdMovie();
  bool removeMovie();
  bool updateMovie();

};

#endif
