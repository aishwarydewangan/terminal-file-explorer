#ifndef LIST_H
#define LIST_H

#include "utils.h"

bool enableNonCanonicalMode();

void disableNonCanonicalMode();

void printBuffer(int low, int high);

void makeDirectoryBuffer(const char *path);

void start(const char * path);

#endif