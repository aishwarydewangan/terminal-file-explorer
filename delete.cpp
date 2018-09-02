#include "include/delete.h"

int deleteFile(const char *name) {
	if(isFileExists(name)) {
		if(remove(name) == 0){
			//File Deleted Successfully
			return 1;
		} else {
			//Error: Cannot delete file. Please check file name!
			return -1;
		}
	} else {
		//Error: File not found. Please check file name!
		return -2;
	}
	return 1;
}

int deleteDirectory(const char *dir) {

	if(isDirectoryExists(dir)) {
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
	} else {
		//Error: Delete Directory does not exists
		return -1;
	}
	return 1;
}