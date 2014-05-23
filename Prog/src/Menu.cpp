/*
 * Menu.cpp
 *
 *  Created on: 22/05/2014
 *      Author: leonardo
 */

#include "Menu.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <limits.h>

#include "Date.h"

class Date;

void Menu::clear() {
	printf("\033[2J\033[1;1H"); //console cleaner
}

int Menu::getch(void) {
	struct termios oldattr, newattr;
	int ch;
	tcgetattr( STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

int Menu::get_key() {
	while (1) {
		int press = getch();
		if (press == 27) {
			if (getch() == 91) {
				int arrow = getch();
				switch (arrow) {
				case 65:
					//cout << "up" << endl;
					return 1;
				case 66:
					//cout << "down" << endl;
					return 2;
					break;
				case 67:
					return 3;
					//cout << "right" << endl;
					break;
				case 68:
					return 4;
					//cout << "left" << endl;
					break;
				default:
					break;
				}
			}
		} else if (press == 113) {
			//cout << "Exit" << endl;
			break;
		} else if (press == 10) {
			return 0;
		}
	}
	return -1;
}

int Menu::create_choice(string message, vector<string> options) {
	int option = 0;
	while (1) {
		clear();
		cout << message << endl << endl;
		for (int i = 0; i < (int) options.size(); ++i) {
			if (option == i)
				cout << "► ";
//			else
			cout << options[i] << endl;
		}
		int choice = get_key();
		switch (choice) {
		case 0:
			return option;
		case 1:
			if (option > 0)
				option--;
			break;
		case 2:
			if (option < (int) options.size() - 1)
				option++;
			break;
		default:
			break;
		}
	}
	return -1;
}

int Menu::get_letter() {
	while (1) {
		int press = getch();
		if ((press >= 65 && press <= 90) || (press >= 97 && press <= 122) || press == 10) {
			return press;
		} else if (press == 195) {
			press = getch();
			if (press == 163)
				return 0;
			else if (press == 161)
				return 1;
			else if (press == 160)
				return 2;
			else if (press == 169)
				return 3;
			else if (press == 173)
				return 4;
			else if (press == 179)
				return 5;
			else if (press == 186)
				return 6;
		} else if (press == 127)
			return -1;
//			getch();
//			getch();
//		}
//		else
//			cout << press << endl;
		//cout << "lele";
	}
	return 0;
}

string Menu::create_search(string message, vector<string> v) {
	string str = "";
	while (1) {
		clear();
		cout << message << endl;
		cout << str;
		cout << endl << "Matches:" << endl;
		for (int i = 0; i < (int) v.size(); ++i) {
			if (v[i].size() >= str.size()) {
				if ((int) v[i].find(str) != -1)
					cout << v[i] << endl;
			}
		}
		int l = get_letter();
		if (l == 10)
			return str;
		if (l == -1) {
			if (str.size() > 0)
				str.resize(str.size() - 1);
		} else if (l > 6)
			str.push_back(l);
		else if (l == 0)
			str.append("ã");
		else if (l == 1)
			str.append("á");
		else if (l == 2)
			str.append("à");
		else if (l == 3)
			str.append("é");
		else if (l == 4)
			str.append("í");
		else if (l == 5)
			str.append("ó");
		else if (l == 6)
			str.append("ú");
	}
	return 0;
}

string Menu::create_reader(string message) {
	clear();
	string str, temp;
	cout << message << endl;
	while (1) {
		try {
			cin.exceptions(istream::failbit | istream::badbit);
			getline(cin,str);
			break;
		} catch (...) {
			cout << "Error in input, please try again" << endl;
		}
		cin.clear();
		cin.ignore();
	}
	//getch();
	return str;
}

void Menu::create_wait(string message) {
	clear();
	cout << message << endl << endl << "[Press any key to continue]" << endl;
	getch();
}

Date Menu::create_time(string message) {
	string week, h, m;
	unsigned int hour;
	unsigned int minutes;
	week = Date::getWeek()[create_choice("Choose day", Date::getWeek())];
	bool valid = true;
	do {
		h = create_reader("Hour?");
		for (int i = 0; i < h.size(); ++i) {
			if (h[i] < '0' && h[i] > '9') {
				valid = false;
				create_wait("Invalid number! (0...23");
			}
		}
		hour = atoi(h.c_str());
	} while (!valid || hour > 23 || hour < 0);
	do {
		m = create_reader("Minutes?");
		for (int i = 0; i < m.size(); ++i) {
			if (m[i] < '0' && m[i] > '9') {
				valid = false;
				create_wait("Invalid number! (0...59)");
			}
		}
		minutes = atoi(m.c_str());
	} while (!valid || minutes > 59 || minutes < 0);
	return Date(week, hour, minutes);
}
