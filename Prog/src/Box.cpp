#include "Box.h"
#include "Menu.h"
#include <sstream>
#include <stdlib.h>     /* atoi */
template<class T>
int member(vector<T> v, T e) {
	for (int i = 0; i < (int) v.size(); ++i) {
		if (v[i] == e)
			return i;
	}
	return -1;
}

string itos(int n) {
	stringstream ss;
	ss << n;
	return ss.str();
}

Box::Box(string passwd, Date date) :
		currentDate(date) {
	password = passwd;
//
//	channels.push_back(Channel("hue1"));
//	channels.push_back(Channel("hue2"));
//	channels.push_back(Channel("hue3"));
//	//channels[1].addProgram(Program("prog",1,"Monday",1,1));
//	recordList.push_back(Program("prog", "tsipo lol", 1, "Monday", 1, 1));
//	recordList.push_back(Program("prog", "tsipo lol", 1, "Monday", 1, 1));

	mlogin.push_back("Admin");
	mlogin.push_back("User");
	mlogin.push_back("Exit");

	madmin.push_back("Edit programs");
	madmin.push_back("Edit movies");
	madmin.push_back("Edit channels");
	madmin.push_back("User menu");
	madmin.push_back("Logout");

	muser.push_back("List programs");
	muser.push_back("Record a program");
	muser.push_back("Rent a movie");
	muser.push_back("Check money spent");
	muser.push_back("List Movies");
	muser.push_back("Logout");

	medit.push_back("Edit");
	medit.push_back("Create");
	medit.push_back("Delete");
	medit.push_back("Back");

	mprogram.push_back("Name");
	mprogram.push_back("Type");
	mprogram.push_back("Duration");
	mprogram.push_back("Exhibition date");
	mprogram.push_back("Back");

	mchannel.push_back("Name");
	mchannel.push_back("Back");

	mmovie.push_back("Title");
	mmovie.push_back("Times rented");
	mmovie.push_back("Cost");
	mmovie.push_back("Back");

	mdayC = mdayA = Date::getWeek();
	mdayA.push_back("Any");
	mdayC.push_back("Current day");
	mlistp.push_back("Day");
	mlistp.push_back("Channel");
	mlistp.push_back("Type");
}

void Box::plister() {
	vector<Program> vp;
	vector<string> vs;
	int choice = Menu::create_choice("List by what?", mlistp);
	if (choice == 0) {
		choice = Menu::create_choice("Which day?", mdayC);
		if (choice < 7)
			vp = listByDay(mdayC[choice]);
		else
			vp = listByDay(Date::currentDate().getWeekDay());

		for (int i = 0; i < vp.size(); ++i) {
			vs.push_back(vp[i].getName());
		}
		choice = Menu::create_choice("Programs for " + mdayC[choice] + " (" + Date::currentDate().getWeekDay() + ")", vs);
	} else if (choice == 1) {
		//TODO TRATAR DE FALHAS DE SEGMENTAÇÃO
		choice = Menu::create_choice("Which day?", mdayA);
		vector<string> vc;
		for (int i = 0; i < channels.size(); ++i) {
			vc.push_back(channels[i].getName());
		}
		string c = channels[Menu::create_choice("Which channel?", vc)].getName();
		if (choice < 7)
			vp = listByChannel(c, mdayA[choice]);
		else
			vp = listByChannel(c);

		vector<string> vs;
		for (int i = 0; i < vp.size(); ++i) {
			vs.push_back(vp[i].getName());
		}
		string day;
		if (choice < 7)
			day = " on " + mdayA[choice];

		choice = Menu::create_choice("Programs from " + c + day, vs);
	} else {
		choice = Menu::create_choice("Which day?", mdayA);
		vector<string> vt;
		for (int i = 0; i < recordList.size(); ++i) {
			if (member(vt, recordList[i].getType()) == -1)
				vt.push_back(recordList[i].getType());
		}
		string t = recordList[Menu::create_choice("Which type?", vt)].getType();
		if (choice < 7)
			vp = listByType(t, mdayA[choice]);
		else
			vp = listByType(t);

		vector<string> vs;
		for (int i = 0; i < vp.size(); ++i) {
			vs.push_back(vp[i].getName());
		}
		string day;
		if (choice < 7)
			day = " on " + mdayA[choice];

		choice = Menu::create_choice("Programs of the " + t + " type" + day, vs);
	}
}

void Box::renter() {
	//TODO TRATAR DE FALHAS DE SEGMENTAÇÃO
	vector<string> vs;
	for (int i = 0; i < movieClub.size(); ++i) {
		vs.push_back(movieClub[i].getTitle());
	}
	for (int i = 0; i < seenMovies.size(); ++i) {
		vs.push_back(seenMovies[i].getTitle());
	}
	int m = Menu::create_choice("Wich movie do you want to rent?", vs);
	int mpos, spos;
	mpos = member(movieClub, Movie(vs[m], 0));
	spos = member(movieClub, Movie(vs[m], 0));
	if (mpos != -1) {
		movieClub[mpos].rent();
		seenMovies.push_back(movieClub[mpos]);
		movieClub.erase(movieClub.begin() + mpos);
	} else if (spos != -1) {
		seenMovies[spos].rent();
	}
	Menu::create_wait("Movie " + vs[m] + " has bee rented!");
}

void Box::spent() {
	int p = 0;
	for (int i = 0; i < seenMovies.size(); ++i) {
		p += seenMovies[i].getCost() * seenMovies[i].getTimesRented();
	}
	Menu::create_wait("A total of " + itos(p) + " moneiz has been spent in rented movies");
}

void Box::rented() {
	vector<string> vs;
	for (int i = 0; i < movieClub.size(); ++i) {
		vs.push_back(movieClub[i].getTitle() + ", seen " + itos(movieClub[i].getTimesRented()) + " times");
	}
	for (int i = 0; i < seenMovies.size(); ++i) {
		vs.push_back(seenMovies[i].getTitle() + ", seen " + itos(seenMovies[i].getTimesRented()) + " times");
	}
	Menu::create_choice("Movies and times rented:", vs);
}

void Box::record() {

//	vector<string> vc;
//	for (int i = 0; i < channels.size(); ++i) {
//		vc.push_back(channels[i].getName());
//	}
//	int c = Menu::create_choice("Where do you want to record a program?", vc);
//
//	bool valid;
//	string name;
//	do {
//		name = Menu::create_reader("Please insert program name:");
//		valid = true;
//		for (int i = 0; i < recordList.size(); ++i) {
//			if (recordList[i].getName() == name) {
//				Menu::create_wait("A program with that already exists, please try again");
//				valid = false;
//			}
//		}
//	} while (!valid);
//	string type = Menu::create_reader("Please insert program type:");
//	string duration;
//	do {
//		duration = Menu::create_reader("Please insert program duration:");
//		valid = true;
//		for (int i = 0; i < duration.size(); ++i) {
//			if (duration[i] < '0' || duration[i] > '9') {
//				Menu::create_wait("Invalid duration, please try again");
//				valid = false;
//				break;
//			}
//		}
//	} while (!valid);
//	int dus = atoi(duration.c_str());
//
//	Date d;
//	//					d=Menu::create_time("Please insert program start time:");
//
//	//					Check date
//
//	Program p(name, type, dus, d);
//	//					channels[c].addProgram(p);
//	recordList.push_back(p);

	Menu::create_wait("TBI");
}

void Box::user() {
	while (1) {
		int choice = Menu::create_choice("What do you want to do?", muser);
		if (choice == 0) {
			if(channels.size()!=0)
						plister();
		} else if (choice == 1) {
			if(channels.size()!=0)
				record();
		} else if (choice == 2) {
			renter();
		} else if (choice == 3) {
			spent();
		} else if (choice == 4) {
			rented();
		} else if (choice == 5)
			break;
	}
}

void Box::movies() {
	int choice;
	while (1) {
		choice = Menu::create_choice("How do you want to edit movies?", medit);
		if (choice == 0) {
			vector<string> vs;
			for (int i = 0; i < (int) movieClub.size(); ++i) {
				vs.push_back(movieClub[i].getTitle());
			}
			for (int i = 0; i < (int) seenMovies.size(); ++i) {
				vs.push_back(seenMovies[i].getTitle());
			}
			string name = Menu::create_search("Please insert the title of the movie", vs);
			int n = member(vs, name);
			if (n == -1) {
				Menu::create_wait("Movie does not exist!");
				break;
			}
			while (1) {
				choice = Menu::create_choice("What do you edit?", mmovie);
				if (choice == 0) {
					string title = Menu::create_reader("Insert new title");
					if (n < movieClub.size())
						movieClub[n].setTitle(title);
					else
						seenMovies[n - movieClub.size()].setTitle(title);
				} else if (choice == 1) {
					bool invalid = true;
					string t;
					while (invalid) {
						invalid = false;
						t = Menu::create_reader("Insert times seen");
						for (int i = 0; i < t.size(); ++i) {
							if (t[i] < '0' || t[i] > '9') {
								Menu::create_wait("Not a number!");
								invalid = true;
								break;
							}
						}
					}
					if (n < movieClub.size())
						movieClub[n].setTimesRented(atoi(t.c_str()));
					else
						seenMovies[n - movieClub.size()].setTimesRented(atoi(t.c_str()));
				} else if (choice == 2) {
					bool invalid = true;
					string t;
					while (invalid) {
						invalid = false;
						t = Menu::create_reader("Insert cost");
						for (int i = 0; i < t.size(); ++i) {
							if (t[i] < '0' || t[i] > '9') {
								Menu::create_wait("Not a number!");
								invalid = true;
								break;
							}
						}
					}
					if (n < movieClub.size()) {
						movieClub[n].setCost(atoi(t.c_str()));
						if (atoi(t.c_str()) > 0) {
							seenMovies.push_back(movieClub[n]);
							movieClub.erase(movieClub.begin() + n);
						}
					} else {
						seenMovies[n - movieClub.size()].setCost(atoi(t.c_str()));
						if (atoi(t.c_str()) == 0) {
							movieClub.push_back(seenMovies[n - movieClub.size()]);
							seenMovies.erase(seenMovies.begin() + n - movieClub.size());
						}
					}
				} else
					break;
			}
		} else if (choice == 1) {
			string title = Menu::create_reader("Insert title");

			string cost;
			bool invalid = true;
			while (invalid) {
				invalid = false;
				cost = Menu::create_reader("Insert cost");
				for (int i = 0; i < cost.size(); ++i) {
					if (cost[i] < '0' || cost[i] > '9') {
						Menu::create_wait("Not a number!");
						invalid = true;
						break;
					}
				}
			}
			movieClub.push_back(Movie(title, atoi(cost.c_str())));

		} else if (choice == 2) {
			vector<string> vs;
			for (int i = 0; i < (int) movieClub.size(); ++i) {
				vs.push_back(movieClub[i].getTitle());
			}
			for (int i = 0; i < (int) seenMovies.size(); ++i) {
				vs.push_back(seenMovies[i].getTitle());
			}
			string name = Menu::create_search("Please insert the title of the movie", vs);
			int n = member(vs, name);
			if (n == -1) {
				Menu::create_wait("Movie does not exist!");
				break;
			}
			if (n < movieClub.size())
				movieClub.erase(movieClub.begin() + n);
			else
				seenMovies.erase(seenMovies.begin() + n - movieClub.size());
		} else if (choice == 3) {
			break;
		}
	}
}

void Box::chans() {
	int choice;
	while (1) {
		choice = Menu::create_choice("How do you want to edit Channels?", medit);
		if (choice == 0) {
			vector<string> vs;
			for (int i = 0; i < (int) channels.size(); ++i) {
				vs.push_back(channels[i].getName());
			}
			string name = Menu::create_search("Please insert the name of the channel", vs);
			int n = member(vs, name);
			if (n == -1) {
				Menu::create_wait("Channel does not exist!");
				break;
			}

			while (1) {
				int e = Menu::create_choice("What do you edit?", mmovie);
				if (e == 1) {
					name = Menu::create_reader("Insert channel name");
					channels[n].setName(name);
				} else
					break;
			}
		} else if (choice == 1) {
			vector<string> vs;
			for (int i = 0; i < (int) channels.size(); ++i) {
				vs.push_back(channels[i].getName());
			}
			string name;
			do {
				name = Menu::create_reader("Insert channel name");
				if (member(vs, name) != -1)
					Menu::create_wait("Movie already exists!");
			} while (member(vs, name) != -1);
			channels.push_back(Channel(name));
		} else if (choice == 2) {
			vector<string> vs;
			for (int i = 0; i < (int) channels.size(); ++i) {
				vs.push_back(channels[i].getName());
			}
			string name = Menu::create_search("Please insert the name of the channel", vs);
			int n = member(vs, name);
			if (n == -1) {
				Menu::create_wait("Channel does not exist!");
				break;
			}
			Menu::create_wait("Channel " + name + " has been deleted!");
			channels.erase(channels.begin() + n);
		} else if (choice == 3) {
			break;
		}
	}
}

void Box::admin() {

	if (Menu::create_reader("Please insert your password:") != password) {
		Menu::create_wait("Wrong Password!\nReturning to login");
		return;
	}
	Menu::create_wait("Welcome to your box Admin!");
	while (1) {
		int choice = Menu::create_choice("What do you want to do?", madmin);
		if (choice == 0) {
//			while (1) {
//				choice = Menu::create_choice("How do you want to edit programs?", medit);
//				if (choice == 0) {
//					vector<string> vs;
//					for (int i = 0; i < recordList.size(); ++i) {
//						vs.push_back(recordList[i].getName());
//					}
//					string name = Menu::create_search("Please insert the name of the program", vs);
//					if (member(vs, name) != -1) {
//						Menu::create_wait("Program does not exist!");
//						break;
//					}
//
//				} else if (choice == 1)
//					;
//				else if (choice == 2)
//					;
//				else
//					break;
//			}
			Menu::create_wait("TBI");
		} else if (choice == 1) {
			movies();
		} else if (choice == 2) {
			chans();
		} else if (choice == 3) {
			user();
		} else if (choice == 4)
			break;
	}

}

int Box::run() {
	while (1) {
		int choice = Menu::create_choice("Please choose a mode:", mlogin);
		if (choice == 0) {
			admin();
		} else if (choice == 1) {
			Menu::create_wait("Welcome to the box!");
			user();
		} else
			break;
	}
	return 0;
}

vector<Program> Box::listByDay(string day) const {
	vector<Program> vp;
	for (int i = 0; i < (int) recordList.size(); ++i) {
		if (recordList[i].getExhibitionDate().getWeekDay() == day)
			vp.push_back(recordList[i]);
	}
	return vp;
}
vector<Program> Box::listByChannel(string channel, string day) const {
	vector<Program> vp;
	for (int i = 0; i < (int) channels.size(); ++i) {
		if (channels[i].getName() == channel) {
			for (int j = 0; j < (int) channels[i].getPrograms().size(); ++j) {
				if (channels[i].getPrograms()[j].getExhibitionDate().getWeekDay() == day)
					vp.push_back(channels[i].getPrograms()[j]);
			}
			break;
		}
	}
	return vp;
}
vector<Program> Box::listByChannel(string channel) const {
	vector<Program> vp;
	for (int i = 0; i < (int) channels.size(); ++i) {
		if (channels[i].getName() == channel) {
			vp = channels[i].getPrograms();
			break;
		}
	}
	return vp;
}
vector<Program> Box::listByType(string type) const {
	vector<Program> vp;
	for (int i = 0; i < (int) recordList.size(); ++i) {
		if (recordList[i].getType() == type)
			vp.push_back(recordList[i]);
	}
	return vp;
}
vector<Program> Box::listByType(string type, string day) const {
	vector<Program> vp;
	for (int i = 0; i < (int) recordList.size(); ++i) {
		if (recordList[i].getType() == type && recordList[i].getExhibitionDate().getWeekDay() == day)
			vp.push_back(recordList[i]);
	}
	return vp;
}
