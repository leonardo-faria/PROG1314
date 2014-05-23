#include <iostream>
#include <cstdlib>
#include "Menu.h"
#include "Date.h"
#include "Box.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main() {
	Date::init();
	Box box = Box("???", Date::currentDate());

	box.run();

	exit(0);
}
