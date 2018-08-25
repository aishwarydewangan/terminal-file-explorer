#include "include/delete.h"

void deleteFile(const char *name) {
	if(isFileExists(name)) {
		if(remove(name) == 0)
			cout << "\nFile Deleted Successfully";
		else
			cout << "\nError: Cannot delete file. Please check file name!";
	} else {
		cout << "\nError: File not found. Please check file name!";
	}
}

void deleteDirectory(const char *dir) {

	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) { 
		printf("Error: Unable to open directory! %s\n", dir);
		return; 
	}

	chdir(dir);

	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			deleteDirectory(entry->d_name);
		}
		else {
			remove(entry->d_name);
		}
	}

	chdir("..");

	rmdir(dir);

	closedir(dp); 
}