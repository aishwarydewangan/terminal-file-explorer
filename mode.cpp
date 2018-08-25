#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

using namespace std;

void printLoremIpsum() {
	cout << "\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sed urna nec mi placerat feugiat";
	cout << "\ntorquent per conubia nostra, per inceptos himenaeos. Interdum et malesuada fames ac ante ipsum ";
	cout << "\nmetus. Curabitur eleifend sem a lorem aliquet, blandit venenatis velit malesuada. Suspendisse posuere velit ";
	cout << "\ncommodo diam pellentesque. Mauris in vehicula metus, vel tempus nunc. Pellentesque placerat massa massa";
	cout << "\nSed vehicula massa nisl, in vestibulum justo feugiat maximus. Cras tristique iaculis orci, et tristique";
}

int main() {

	struct termios oldTerm, newTerm;

	tcgetattr(STDIN_FILENO, &oldTerm);

	newTerm = oldTerm;

	newTerm.c_lflag &= ~(ICANON|ECHO);

	if(tcsetattr(STDIN_FILENO, TCSANOW, &newTerm) != 0) {
		cout << "\nError: Cannot go to Non-Canonical Mode";
	}

	cout << "\e[2J";
	cout << "\e[32;44m";

	printLoremIpsum();

	cout << "\e[0;0H";

	char c;

	while(1) {
		c = getchar();

		if(c == ':')
			cout << "\nCommand Mode";

		if(c == '\033') { 

			//Normal Mode

			while(c != ':') {

				c = getchar();

				if(c == 65) 
					cout << "\e[1A";

				if(c == 66)
					cout << "\e[1B";

				if(c == 68)
					cout << "\e[1D";

				if(c == 67)
					cout << "\e[1C";
			}
		}

		if(c == 'q') {
			cout << "\nQuitting...";
			break;
		}
	}

	cout << "\e[2J";
	cout << "\e[32;44m";

	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);

	return 0;
}