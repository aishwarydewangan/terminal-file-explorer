#include "include/delete.h"

void deleteFile(const char *name) {

	printf("\e[26;1H");
	printf("\e[K");

	if(isFileExists(name)) {
		if(remove(name) == 0){
			printf("\e[26;1HSuccess: File Deleted.");
		} else {
			printf("\e[26;1HError: Cannot delete file. Please check file permissions.");
		}
	} else {
		printf("\e[26;1HError: File not found. Please check file name.");
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
			printf("\e[26;1HError: Unable to open Directory.");
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
		
		printf("\e[26;1HSuccess: Directory deleted.");
	} else {
		printf("\e[26;1HError: Directory does not exists.");
	}
}