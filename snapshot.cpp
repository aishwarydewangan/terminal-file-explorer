/******************************
Created By: Aishwary Dewangan
Course: M. Tech. CSIS
Roll No.: 2018202016
GitLab Handle: aish_2018202016
******************************/

#include "include/snapshot.h"

vector<string> snapshotBuffer;

void snapshot(const char *dir) {

	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	if((dp = opendir(dir)) == NULL) { 
		printStatus("Error: Unable to open directory.");
		return; 
	}

	chdir(dir);

	string df("\n\n"), de(":\n"), fe("\t");

	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name,&statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue; 
			snapshotBuffer.push_back(df + entry->d_name + de);
			snapshot(entry->d_name);
		}
		else {
			snapshotBuffer.push_back(entry->d_name + fe);
		}
	}

	chdir("..");

	closedir(dp); 
}

vector<string> getSnapshot(const char *dir) {
	snapshot(dir);
	return snapshotBuffer;
}