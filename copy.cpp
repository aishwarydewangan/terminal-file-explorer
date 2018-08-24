#include <iostream>
#include <fstream>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <limits.h>
#include <stdlib.h>

using namespace std;

vector<string> filePaths, directoryPaths;

bool isFileExists(const char *name) {
	ifstream file(name);
	bool check = file.good();
	file.close();
	return check;
}

bool isDirectoryExists(const char *name) {
	struct stat st;
	if(stat(name, &st) == -1) 
		return false;
	return true;
}

void copyFile(const char *sourceFile, const char *destinationFile) {
	if(isFileExists(sourceFile)) {
		if(!isFileExists(destinationFile)) {	
			char buf[BUFSIZ];
		    size_t size;

		    int source = open(sourceFile, O_RDONLY, 0);
		    int dest = open(destinationFile, O_WRONLY | O_CREAT , 0644);

		    while ((size = read(source, buf, BUFSIZ)) > 0) {
		        write(dest, buf, size);
		    }

		    close(source);
		    close(dest);
		} else {
			cout << "\nError: Destination File already exists. Please check name!";
		}
	} else {
		cout << "\nError: Source File not found. Please check name!";
	}
}

void index(string sourceDirectory) {
	DIR *dp;
	struct dirent *entry; 
	struct stat statbuf;

	if((dp = opendir(sourceDirectory.c_str())) == NULL) { 
		printf("Error: Unable to open directory! %s\n", sourceDirectory.c_str());
		return; 
	}

	chdir(sourceDirectory.c_str());

	while((entry = readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf); 
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
				continue;
			directoryPaths.push_back(realpath(entry->d_name, NULL));
			index(entry->d_name);
		}
		else {
			filePaths.push_back(realpath(entry->d_name, NULL));
		}
	}

	chdir("..");

	closedir(dp); 
}

void copyDirectory(string sourceDirectory, string destinationDirectory) {

	string sourceAbsolutePath(realpath(sourceDirectory.c_str(), NULL));

	string destinationAbsolutePath(realpath(destinationDirectory.c_str(), NULL));

	int pos = sourceAbsolutePath.find_last_of('/');

	string sourceName = sourceAbsolutePath.substr(pos+1);

	index(realpath(sourceDirectory.c_str(), NULL));

	string home(destinationAbsolutePath + '/' + sourceName);

	mkdir(home.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

	for(int i = 0; i < directoryPaths.size(); i++) {
		string temp = destinationAbsolutePath + directoryPaths[i].substr(pos);
		mkdir(temp.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}

	for(int i = 0; i < filePaths.size(); i++) {
		string temp = destinationAbsolutePath + filePaths[i].substr(pos);
		copyFile(filePaths[i].c_str(), temp.c_str());
	}
}

int main() {
	//copyFile("hello.txt", "hey.txt");

	copyDirectory("dsa", "/Users/aishwary/Desktop/testing");

	cout << endl;

	return 0;
}