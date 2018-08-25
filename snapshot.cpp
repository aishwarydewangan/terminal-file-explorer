#include "include/snapshot.h"

void snapshot(const char *dir, int depth) {

	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) { 
		printf("Error: Unable to open directory! %s\n", dir);
		return; 
	}

	chdir(dir);

	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue; 
			printf("%*s%s/\n", depth,"",entry->d_name);
			snapshot(entry->d_name, depth+4);
		}
		else 
			printf("%*s%s\n", depth, "",entry->d_name); 
	}

	chdir("..");

	closedir(dp); 

}