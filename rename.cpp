#include <cstdio>
#include <iostream>

using namespace std;

void newName(const char *oldFileName, const char *newFileName) {
	int status = rename(oldFileName, newFileName);
	if(status == 0)
		cout << "\nFile renamed successfully";
	else
		cout << "\nError: Cannot rename file. Please check for permissions!";
}

int main() {
	newName("hello.txt", "hey.mp4");
	return 0;
}