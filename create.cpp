#include "include/create.h"

int createFile(const char *name) {
	if(!isFileExists(name)) {
		ofstream outFile(name);
		outFile.close();
	} else {
		//Error: File already exists. Please check name!
		return -1;
	}
	return 1;
}

int createDirectory(const char *name) {
	struct stat st;
	if(stat(name, &st) == -1) {
		mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
	} else {
		//Error: Directory already exists. Please check name!
		return -1;
	}
	return 1;
}