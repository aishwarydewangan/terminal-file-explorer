#include <unistd.h>
#include <cstdio>
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

void deleteFile(const char *name) {
	if(!isFileExists(name)) {
		if(remove(name) == 0)
			cout << "\nFile Deleted Successfully";
		else
			cout << "\nError: Cannot delete file. Please check file name!";
	} else {
		cout << "\nError: File not found. Please check file name!";
	}
}

void traverse(const char *dir) {

	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	//Check whether directory can be opened or not
	if((dp = opendir(dir)) == NULL) { 
		printf("Error: Unable to open directory! %s\n", dir);
		return; 
	}

	chdir(dir);

	//Recurse through each directory
	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			traverse(entry->d_name);
		}
		else {
			remove(entry->d_name);
		}
	}

	chdir("..");

	rmdir(dir);

	closedir(dp); 
}

int main() {
	//deleteFile("hello.txt");

	traverse("dsa");
	return 0;
}