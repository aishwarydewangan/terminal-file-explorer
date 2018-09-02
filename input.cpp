#include "include/copy.h"
#include "include/create.h"
#include "include/delete.h"
#include "include/list.h"
#include "include/move.h"
#include "include/rename.h"
#include "include/search.h"

using namespace std;

struct termios oldTerm, newTerm;

void refreshScreen() {
	printf("\e[2J");
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

bool isFile(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

bool isDirectory(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

vector<string> tokenizeString(string str, string delim) {
	vector<string> v;
	char *temp = new char[str.size()+1];
	strcpy(temp, str.c_str());
	char *token = strtok(temp, delim.c_str());
	while (token != NULL)
    {
    	v.push_back(token);
        token = strtok(NULL, delim.c_str());
    }
    delete [] temp;

    return v;
}


int main() {
	enableNonCanonicalMode();
	refreshScreen();
	char c;
	string s;
	int leftPos = 1, i = 0;
	vector<string> v;

	printf("\e[1;1H");
	while(1) {
		c = getchar();
		if(c == 10)
			break;
		printf("\e[1;%dH%c", leftPos, c);
		s.push_back(c);
		leftPos++;
		if(c == 127) {
			printf("\e[1;1H");
			printf("\e[K");
			s.pop_back();
			s.pop_back();
			leftPos -= 2;
			printf("\e[1;1H%s", s.c_str());
			printf("\e[1;%dH", leftPos);
		}
	}

	v = tokenizeString(s, " ");

    if(isDirectory(v[v.size()-1].c_str())) {

    	if(strcmp(v[v.size()-1].c_str(), "/") == 0)
    	v[v.size()-1].pop_back();

		if(strcmp(v[0].c_str(), "copy") == 0) {
			for(int i = 1; i < v.size()-1; i++) {
				if(isFile(v[i].c_str())) {
					vector<string> name = tokenizeString(v[i], "/");

				    string basePath = v[v.size()-1];

				    string dest = basePath + "/" + name[name.size()-1];

					int status = copyFile(v[i].c_str(), dest.c_str());

					cout << "\n\tStatus: " << status;
				}

				if(isDirectory(v[i].c_str())) {
					int status = copyDirectory(v[i], v[v.size()-1]);

					cout << "\n\tStatus: " << status;
				}
			}
		}

		if(strcmp(v[0].c_str(), "move") == 0) {
			for(int i = 1; i < v.size()-1; i++) {
				if(isFile(v[i].c_str())) {
					vector<string> name = tokenizeString(v[i], "/");

				    string basePath = v[v.size()-1];

				    string dest = basePath + "/" + name[name.size()-1];

					int status = moveFile(v[i].c_str(), dest.c_str());

					cout << "\n\tStatus: " << status;
				}

				if(isDirectory(v[i].c_str())) {
					int status = moveDirectory(v[i], v[v.size()-1]);

					cout << "\n\tStatus: " << status;
				}
			}
		}

		if(strcmp(v[0].c_str(), "create_file") == 0) {
			for(int i = 1; i < v.size()-1; i++) {
				string basePath = v[v.size()-1];

				//if(strcmp(basePath.c_str(), ".") == 0)
				//Complete this

				string dest = basePath + "/" + v[i];

				int status = createFile(dest.c_str());

				cout << "\nStatus: " << status;
			}
		}

		if(strcmp(v[0].c_str(), "create_dir") == 0) {
			for(int i = 1; i < v.size()-1; i++) {
				string basePath = v[v.size()-1];

				//if(strcmp(basePath.c_str(), ".") == 0)
				//Complete this

				string dest = basePath + "/" + v[i];

				int status = createDirectory(dest.c_str());

				cout << "\nStatus: " << status;
			}
		}

    } else
    	cout << "\nDestination is not a directory.";

    if(strcmp(v[0].c_str(), "delete") == 0) {
		for(int i = 1; i < v.size(); i++) {
			if(isFile(v[i].c_str())) {

				deleteFile(v[i].c_str());

				//cout << "\n\tStatus: " << status;
			}

			if(isDirectory(v[i].c_str())) {
				deleteDirectory(v[i].c_str());
			}
		}
	}

	getchar();

	disableNonCanonicalMode();

	refreshScreen();

	return 0;
}

