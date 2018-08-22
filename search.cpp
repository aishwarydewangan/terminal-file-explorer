#include <unistd.h> 
#include <stdio.h> 
#include <dirent.h> 
#include <string.h> 
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int flag;

void traverse(const char *dir, const char *name) {

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
			if(strcmp(entry->d_name, name) == 0) {
				cout << "\nFound directory";
				cout << "\nAbsolute Path: " << realpath(entry->d_name, NULL);
				flag = 1;
			}
			traverse(entry->d_name, name);
		}
		else {
			if(strcmp(entry->d_name, name) == 0) {
				cout << "\nFound file";
				cout << "\nAbsolute Path: " << realpath(entry->d_name, NULL);
				flag = 1;
			}
		}
	}

	chdir("..");

	closedir(dp); 

}

void search(const char *dir, const char *name) {
	flag = 0;

	traverse(dir, name);

	if(flag == 0)
		cout << "\nError: File/Directory not found";
}

int main() {

	search("/Users/aishwary/Desktop", "dsa");

	return 0;
}