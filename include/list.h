#ifndef LIST_H
#define LIST_H

#include "utils.h"

string check(unsigned const char type);

vector<string> getListBuffer(const char *path);

vector<string> getDirectoryBuffer(const char *path);

string getPermissions(struct stat sb);

#endif