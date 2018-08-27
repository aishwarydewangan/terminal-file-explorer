#include "include/list.h"

struct termios oldTerm, newTerm;

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
	printf("\e[2J");

	printf("\e[1;1H");

	tcsetattr(STDIN_FILENO, TCSANOW, &oldTerm);
}

void printBuffer(vector<string> listBuffer, int low, int high) {
	printf("\e[2J");

	printf("\e[1;1H");

	for(int i = low; i <= high; i++) {
		char *listLine = new char[listBuffer[i].length()+1];
		strcpy(listLine, listBuffer[i].c_str());
		char *token = strtok(listLine, "/");
		while (token != NULL)
	    {
	    	printf("%-12s", token);
	        token = strtok(NULL, "/");
	    }
	    delete [] listLine;
	}

	printf("\e[1;1H");
}

int main() {

	if(enableNonCanonicalMode()) {

		vector<string> listBuffer = getListBuffer("/Users/aishwary/Desktop/testing");

		vector<string> directoryBuffer = getDirectoryBuffer("/Users/aishwary/Desktop/testing");

		printf("\e[2J");

		printBuffer(listBuffer, 0, 19);

		int low = 0, high = 19, cursorPos = 1, MAX_POS = listBuffer.size()-1;

		printf("\e[1;1H");

		char c;

		while(1) {

			c = getchar();

			if(c == 65) {
				if(cursorPos == 1) {
					if(low > 0) {
						low--;
						high--;
					}
					printBuffer(listBuffer, low, high);
				}

				if(cursorPos > 1) {
					cursorPos--;
				}

				printf("\e[1A");
			}

			if(c == 66) {
				if(cursorPos == 20) {
					if(high < MAX_POS) {
						low++;
						high++;
					}
					printBuffer(listBuffer, low, high);
				}

				if(cursorPos < 20) {
					cursorPos++;	
				}
				printf("\e[1B");
			}

			if(c == 68)
				printf("\e[1D");

			if(c == 67)
				printf("\e[1C");

			if(c == 'q') {
				break;
			}

			printf("\e[%d;1H", cursorPos);
		}

		disableNonCanonicalMode();
	}
	return 0;
}