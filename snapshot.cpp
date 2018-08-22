#include <unistd.h> 
#include <stdio.h> 
#include <dirent.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <stdlib.h>

void snapshot(const char *dir, int depth) {

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
		lstat(entry->d_name,&statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue; 
			printf("%*s%s/\n", depth,"",entry->d_name);
			printdir(entry->d_name, depth+4);
		}
		else 
			printf("%*s%s\n", depth, "",entry->d_name); 
	}

	chdir("..");

	closedir(dp); 

}

int main() {
	snapshot("/Users/aishwary/Desktop", 0);
	return 0;
}