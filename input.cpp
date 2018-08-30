#include "include/list.h"

struct termios oldTerm, newTerm;

void refreshScreen() {
  write(STDOUT_FILENO, "\x1b[2J", 4);
}

bool enableNonCanonicalMode() {
	tcgetattr(STDIN_FILENO, &oldTerm);

	newTerm = oldTerm;

	newTerm.c_lflag &= ~(ICANON);

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
	while(1) {
		c = getchar();
		s.push_back(c);
		if(c == 10)
			break;

	}

	disableNonCanonicalMode();

	string cmd;

	int i = 0;

	while(s[i] != ' ') {
		cmd.push_back(s[i]);
		i++;
	}
	cmd.push_back('\0');

	if(strcmp(cmd.c_str(), "copy") == 0)
		cout << "\ncopy Encountered";

	if(cmd == "create_file")
		cout << "\ncreate_file Encountered";

	if(cmd == "create_dir")
		cout << "\ncreate_dir Encountered";

	if(cmd == "move")
		cout << "\nmove Encountered";

	if(cmd == "delete")
		cout << "\ndelete Encountered";

	return 0;
}
