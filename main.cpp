#include "include/list.h"
#include "include/create.h"
#include "include/copy.h"
#include "include/move.h"
#include "include/delete.h"

struct termios oldTerm, newTerm;

struct dirent **directoryContents;

static int directoryNum;

vector<string> listBuffer;

stack<string> forwardPath, backwardPath;

string root = "/Users/aishwary/Desktop/testing";

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

void executeCommand(string ip) {
	vector<string> cmdTokens = tokenizeString(ip, " ");

	if(strcmp(cmdTokens[0].c_str(), "delete") == 0) {
		for(int i = 1; i < cmdTokens.size(); i++) {
			if(isFile(cmdTokens[i].c_str())) {
				deleteFile(cmdTokens[i].c_str());
			}
			if(isDirectory(cmdTokens[i].c_str())) {
				deleteDirectory(cmdTokens[i].c_str());
			}
		}
		return;
	}

	if(isDirectory(cmdTokens[cmdTokens.size()-1].c_str())) {

		if(strcmp(cmdTokens[cmdTokens.size()-1].c_str(), "/") == 0)
			cmdTokens[cmdTokens.size()-1].pop_back();

		if(strcmp(cmdTokens[0].c_str(), "copy") == 0) {
			for(int i = 1; i < cmdTokens.size()-1; i++) {
				if(isFile(cmdTokens[i].c_str())) {
					vector<string> name = tokenizeString(cmdTokens[i], "/");

					string basePath = cmdTokens[cmdTokens.size()-1];

					string dest = basePath + "/" + name[name.size()-1];

					copyFile(cmdTokens[i].c_str(), dest.c_str());
				}

				if(isDirectory(cmdTokens[i].c_str())) {
					copyDirectory(cmdTokens[i], cmdTokens[cmdTokens.size()-1]);
				}
			}
		}

		if(strcmp(cmdTokens[0].c_str(), "move") == 0) {
			for(int i = 1; i < cmdTokens.size()-1; i++) {
				if(isFile(cmdTokens[i].c_str())) {
					vector<string> name = tokenizeString(cmdTokens[i], "/");

					string basePath = cmdTokens[cmdTokens.size()-1];

					string dest = basePath + "/" + name[name.size()-1];

					moveFile(cmdTokens[i].c_str(), dest.c_str());
				}

				if(isDirectory(cmdTokens[i].c_str())) {
					moveDirectory(cmdTokens[i], cmdTokens[cmdTokens.size()-1]);
				}
			}
		}

		if(strcmp(cmdTokens[0].c_str(), "create_file") == 0) {
			for(int i = 1; i < cmdTokens.size()-1; i++) {
				string basePath = cmdTokens[cmdTokens.size()-1];

				//if(strcmp(basePath.c_str(), ".") == 0)
				//Complete this

				string dest = basePath + "/" + cmdTokens[i];

				createFile(dest.c_str());
			}
		}

		if(strcmp(cmdTokens[0].c_str(), "create_dir") == 0) {
			for(int i = 1; i < cmdTokens.size()-1; i++) {
				string basePath = cmdTokens[cmdTokens.size()-1];

				//if(strcmp(basePath.c_str(), ".") == 0)
				//Complete this

				string dest = basePath + "/" + cmdTokens[i];

				createDirectory(dest.c_str());
			}
		}
	} else {
		printf("\e[26;1H");
		printf("\e[K");
		printf("\e[26;1HError: Destination is not a directory.");
	}
}

void commandMode(string currentPath) {
	printf("\e[28;1H:");

	char c;

	string ip;

	int leftPos = 2;

	bool execFlag = false;

	while(1) {
		c = getchar();

		if(c == 27)
			break;

		if(c == 10) {
			execFlag = true;
		}

		if(execFlag) {
			executeCommand(ip);
			printf("\e[28;1H");
			printf("\e[K");
			ip.clear();
			leftPos = 2;
			execFlag = false;
			printf("\e[28;1H:");
		} else {
			printf("\e[28;%dH%c", leftPos, c);

			ip.push_back(c);

			leftPos++;

			if(c == 127) {
				printf("\e[28;1H");
				printf("\e[K");
				ip.pop_back();
				ip.pop_back();
				leftPos -= 2;
				printf("\e[28;1H:%s", ip.c_str());
				printf("\e[28;%dH", leftPos);
			}
		}
	}

	printf("\e[28;1H");
	printf("\e[K");
}

void start(string path) {

	if(enableNonCanonicalMode()) {

		refreshScreen();

		makeDirectoryBuffer(path.c_str());

		forwardPath.push(path);

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


			//Left
			if(c == 68) { 
				if(forwardPath.size() > 1) {
					backwardPath.push(forwardPath.top());
					forwardPath.pop();
					string fullPath = forwardPath.top();

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

			//Right
			if(c == 67) {
				if(backwardPath.size() > 0) {
					string fullPath;
					fullPath = backwardPath.top();
					backwardPath.pop();
					forwardPath.push(fullPath);

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

			if(c == 10) {

				string fullPath;

				if(check(directoryContents[low+cursorPos-1]->d_type) == "Directory") {

					if(low+cursorPos-1 != 0) {

						if(directoryContents[low+cursorPos-1]->d_name == "..") {
							if(forwardPath.size() > 1) {
								fullPath = forwardPath.top();
								forwardPath.pop();
								backwardPath.push(fullPath);
							}
						} else {
							fullPath = realpath(directoryContents[low+cursorPos-1]->d_name, NULL);
							forwardPath.push(fullPath);
						}

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

				if(check(directoryContents[low+cursorPos-1]->d_type) ==  "File") {
					printf("\e[25;1HYet to implement");
				}
			}

			if(c == 58) {
				commandMode(forwardPath.top());
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
	start(root);
	return 0;
}
