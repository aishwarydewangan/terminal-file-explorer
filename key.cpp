#include "include/list.h"

struct termios oldTerm, newTerm;

void refreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
}

bool enableNonCanonicalMode() {
	tcgetattr(STDIN_FILENO, &oldTerm);

	newTerm = oldTerm;

	newTerm.c_lflag &= ~(ICANON|ECHO);

	if(tcsetattr(STDIN_FILENO, TCSANOW, &newTerm) != 0) {
		cout << "\nError: Cannot go to Non-Canonical Mode";
		return false;
	}
	return true;
}

void disableNonCanonicalMode() {
	refreshScreen();

	printf("\e[1;1H");

	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
}

int main() {
	enableNonCanonicalMode();
	refreshScreen();
	char c;
	string s;
	int leftPos = 1;
	printf("\e[1;1H");
	while(1) {
		c = getchar();
		printf("%d", c);
		if(c == 'q')
			break;

	}

	disableNonCanonicalMode();

	refreshScreen();

	return 0;
}
