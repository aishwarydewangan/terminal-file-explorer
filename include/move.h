#ifndef MOVE_H
#define MOVE_H

#include "utils.h"
#include "copy.h"
#include "delete.h"

int moveFile(const char *sourceFile, const char *destinationFile);

int moveDirectory(string sourceDirectory, string destinationDirectory);

#endif