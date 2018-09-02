#include "include/create.h"

void createFile(const char *name) {

	if(!isFileExists(name)) {
		ofstream outFile(name);
		outFile.close();
		printStatus("Success: File created successfully.");
	} else {
		printStatus("Error: File already exists. Please check name.");
	}
}

void createDirectory(const char *name) {

	struct stat st;
	if(stat(name, &st) == -1) {
		mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
		printStatus("Success: Directory created successfully.");
	} else {
		printStatus("Error: Directory already exists. Please check name.");
	}
}