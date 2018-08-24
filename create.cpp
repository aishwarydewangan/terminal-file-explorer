#include <iostream>
#include <fstream>
#include <dirent.h> 
#include <sys/stat.h> 

using namespace std;

bool isFileExists(const char *name) {
	ifstream file(name);
	bool check = file.good();
	file.close();
	return check;
}

void createFile(const char *name) {
	if(!isFileExists(name)) {
		ofstream outfile(name);
		outfile.close();
	} else {
		cout << "\nError: File already exists. Please check name!";
	}
}

void createDirectory(const char *name) {
	struct stat st;
	if(stat(name, &st) == -1) {
		mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
	} else {
		cout << "\nError: Directory already exists. Please check name!";
	}

}

int main() {
	createFile("hello.txt");
	createDirectory("Hello");
	return 0;
}