/*
 * Menu.h
 *
 *  Created on: 22/05/2014
 *      Author: leonardo
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include <vector>

class Date;

using namespace std;
class Menu {
public:
	static void clear();
	static int getch();
	static int get_key();
	static int get_letter();
	static int create_choice(string message, vector<string> options);
	static string create_search(string message, vector<string> v);
	static string create_reader(string message);
	static void create_wait(string message);
	static Date create_time(string message);
};

#endif /* MENU_H_ */
