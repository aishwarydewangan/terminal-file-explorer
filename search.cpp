#include "include/search.h"

int flag;

void traverse(const char *dir, const char *name) {

	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) { 
		printStatus("Error: Unable to open directory.");
		return; 
	}

	chdir(dir);

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