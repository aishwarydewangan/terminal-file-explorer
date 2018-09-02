#ifndef UTILS_H
#define UTILS_H

#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>

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

inline string check(unsigned const char type) {
    if(type == DT_REG)
        return "File";
    if(type == DT_DIR)
        return "Directory";
    return "None";
}

inline bool isFile(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISREG(buf.st_mode);
}

inline bool isDirectory(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

inline void printStatus(const char *status) {
	printf("\e[26;1H");
	printf("\e[K");
	printf("\e[26;1H%s", status);
}

inline vector<string> tokenizeString(string str, string delim) {
	vector<string> v;
	char *temp = new char[str.size()+1];
	strcpy(temp, str.c_str());
	char *token = strtok(temp, delim.c_str());
	while (token != NULL)
    {
    	v.push_back(token);
        token = strtok(NULL, delim.c_str());
    }
    delete [] temp;

    return v;
}

inline string getPermissions(struct stat sb) {
	string permissions;

	permissions.push_back((S_ISDIR(sb.st_mode)) ? 'd' : '-');
	permissions.push_back((sb.st_mode & S_IRUSR) ? 'r' : '-');
	permissions.push_back((sb.st_mode & S_IWUSR) ? 'w' : '-');
	permissions.push_back((sb.st_mode & S_IXUSR) ? 'x' : '-');
	permissions.push_back((sb.st_mode & S_IRGRP) ? 'r' : '-');
	permissions.push_back((sb.st_mode & S_IWGRP) ? 'w' : '-');
	permissions.push_back((sb.st_mode & S_IXGRP) ? 'x' : '-');
	permissions.push_back((sb.st_mode & S_IROTH) ? 'r' : '-');
	permissions.push_back((sb.st_mode & S_IWOTH) ? 'w' : '-');
	permissions.push_back((sb.st_mode & S_IXOTH) ? 'x' : '-');

	return permissions;
}

#endif