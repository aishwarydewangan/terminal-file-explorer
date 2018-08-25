#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>

using namespace std;

inline bool isFileExists(const char *name) {
	ifstream file(name);
	bool check = file.good();
	file.close();
	return check;
}

inline bool isDirectoryExists(const char *name) {
	struct stat st;
	if(stat(name, &st) == -1) 
		return false;
	return true;
}

#endif