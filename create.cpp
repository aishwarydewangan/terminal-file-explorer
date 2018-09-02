#include "include/create.h"

void createFile(const char *name) {

	printf("\e[26;1H");
	printf("\e[K");

	if(!isFileExists(name)) {
		ofstream outFile(name);
		outFile.close();
		printf("\e[26;1HSuccess: File created successfully.");
	} else {
		printf("\e[26;1HError: File already exists. Please check name.");
	}
}

void createDirectory(const char *name) {

	printf("\e[26;1H");
	printf("\e[K");

	struct stat st;
	if(stat(name, &st) == -1) {
		mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
		printf("\e[26;1HSuccess: Directory created successfully.");
	} else {
		printf("\e[26;1HError: Directory already exists. Please check name.");
	}
}