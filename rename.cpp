#include <cstdio>
#include <iostream>

using namespace std;

bool isFileExists(const char *name) {
	ifstream file(name);
	bool check = file.good();
	file.close();
	return check;
}

void renameFile(const char *oldFileName, const char *newFileName) {
	if(isFileExists(oldFileName)) {
		if(!isFileExists(newFileName)) {	
			int status = rename(oldFileName, newFileName);
			if(status == 0)
				cout << "\nFile renamed successfully";
			else
				cout << "\nError: Cannot rename file. Please check for permissions!";
		} else {
			cout << "\nError: Destination File already exists. Please check name!";
		}
	} else {
		cout << "\nError: Source File not found. Please check name!";
	}
}

int main() {
	renameFile("hello.txt", "hey.mp4");
	return 0;
}