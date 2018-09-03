/******************************
Created By: Aishwary Dewangan
Course: M. Tech. CSIS
Roll No.: 2018202016
GitLab Handle: aish_2018202016
******************************/

#include "include/delete.h"

void deleteFile(const char *name) {

	if(isFileExists(name)) {
		if(remove(name) == 0){
			printStatus("Success: File Deleted.");
		} else {
			printStatus("Error: Cannot delete file. Please check file permissions.");
		}
	} else {
		printStatus("Error: File not found. Please check file name.");
	}
}

void deleteDirectory(const char *dir) {

	printf("\e[26;1H");
	printf("\e[K");

	if(isDirectoryExists(dir)) {
		DIR *dp;
		struct dirent *entry; 
		struct stat statbuf;

		if((dp = opendir(dir)) == NULL) { 
			printStatus("Error: Unable to open Directory.");
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
		
		printStatus("Success: Directory deleted.");
	} else {
		printStatus("Error: Directory does not exists.");
	}
}