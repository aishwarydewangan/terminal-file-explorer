/******************************
Created By: Aishwary Dewangan
Course: M. Tech. CSIS
Roll No.: 2018202016
GitLab Handle: aish_2018202016
******************************/

#ifndef LIST_H
#define LIST_H

#include "utils.h"

bool enableNonCanonicalMode();

void disableNonCanonicalMode();

void printBuffer(int low, int high);

void makeDirectoryBuffer(const char *path);

void start(string path);

#endif