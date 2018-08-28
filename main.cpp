#include "include/list.h"

struct termios oldTerm, newTerm;

struct dirent **directoryContents;

static int directoryNum;

vector<string> listBuffer;

stack<string> stkPath;

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

void printBuffer(int low, int high) {
	refreshScreen();

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

void makeDirectoryBuffer(const char *path) {

	chdir(path);

	int n = scandir(".", &directoryContents, NULL, alphasort);

	if (n == -1) {
       perror("scandir");
       exit(EXIT_FAILURE);
   	}

   	directoryNum = n;

   	for(int i = 0; i < n; i++) {
   		string str;
		struct stat sb;
		stat(directoryContents[i]->d_name, &sb);
		str = directoryContents[i]->d_name;
		str = str + "/" + getPermissions(sb) + "/";
		str = str + getpwuid(sb.st_uid)->pw_name + "/";
		str = str + getgrgid(sb.st_gid)->gr_name + "/";
		str = str + ctime(&sb.st_mtime);
		listBuffer.push_back(str);
   	}
}

void start(string path) {

	if(enableNonCanonicalMode()) {

		refreshScreen();

		makeDirectoryBuffer(path.c_str());

		stkPath.push(path);

		int low, high, cursorPos, MAX_POS, MAX_CPOS;

		low = 0;

		high = (listBuffer.size()-1 < 19) ? listBuffer.size()-1 : 19;

		cursorPos = 1;

		MAX_POS = listBuffer.size()-1;

		MAX_CPOS = (directoryNum < 20) ? directoryNum : 20;

		printBuffer(low, high);

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
					printBuffer(low, high);
				}

				if(cursorPos > 1) {
					cursorPos--;
				}

				printf("\e[1A");
			}

			if(c == 66) {
				if(cursorPos == MAX_CPOS) {
					if(high < MAX_POS) {
						low++;
						high++;
					}
					printBuffer(low, high);
				}

				if(cursorPos < MAX_CPOS) {
					cursorPos++;	
				}
				printf("\e[1B");
			}

			if(c == 10) {

				string fullPath;

				if(directoryContents[low+cursorPos-1]->d_name != ".") {

					if(directoryContents[low+cursorPos-1]->d_name == "..")
						fullPath = stkPath.top();
					else
						fullPath = realpath(directoryContents[low+cursorPos-1]->d_name, NULL);

					listBuffer.clear();

					free(directoryContents);

					makeDirectoryBuffer(fullPath.c_str());

					low = 0;

					high = (listBuffer.size()-1 < 19) ? listBuffer.size()-1 : 19;

					cursorPos = 1;

					MAX_POS = listBuffer.size()-1;

					MAX_CPOS = (directoryNum < 20) ? directoryNum : 20;

					printBuffer(low, high);	
				}
			}

			if(c == 'q') {
				break;
			}

			printf("\e[%d;1H", cursorPos);
		}

		disableNonCanonicalMode();
	}
}

int main() {
	start("/Users/aishwary/Desktop/testing");
	return 0;
}
