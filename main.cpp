#include "include/list.h"

struct termios oldTerm, newTerm;

struct dirent **directoryContents;

vector<string> listBuffer;

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

void printBuffer(int low, int high) {
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

void makeDirectoryBuffer(const char *path) {

	int n = scandir(path, &directoryContents, NULL, alphasort);

	if (n == -1) {
       perror("scandir");
       exit(EXIT_FAILURE);
   	}

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

   	free(directoryContents);
}

void start(const char * path) {

	if(enableNonCanonicalMode()) {

		printf("\e[2J");

		makeDirectoryBuffer(path);

		printBuffer(0, 19);

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
					printBuffer(low, high);
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
					printBuffer(low, high);
				}

				if(cursorPos < 20) {
					cursorPos++;	
				}
				printf("\e[1B");
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
/*

int test() {

	//show("/Users/aishwary/Desktop/");

	createFile("hello.txt");
	
	//createDirectory("Hello");

	//copyFile("hello.txt", "hey.txt");

	//copyDirectory("dsa", "/Users/aishwary/Desktop/testing");

	//deleteFile("/Users/aishwary/Desktop/hello.txt");

	//deleteDirectory("");

	//moveFile("hello.txt", "hey.txt");

	//moveDirectory("dsa", "/Users/aishwary/Desktop/testing");

	renameFile("hello.txt", "hey.mp4");

	search("/Users/aishwary/Desktop", "dsa");

	//snapshot("/Users/aishwary/Desktop", 0);

	return 0;
}
*/
