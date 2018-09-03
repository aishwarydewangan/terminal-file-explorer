/******************************
Created By: Aishwary Dewangan
Course: M. Tech. CSIS
Roll No.: 2018202016
GitLab Handle: aish_2018202016
******************************/

#ifndef MOVE_H
#define MOVE_H

#include "utils.h"
#include "copy.h"
#include "delete.h"

void moveFile(const char *sourceFile, const char *destinationFile);

void moveDirectory(string sourceDirectory, string destinationDirectory);

#endif