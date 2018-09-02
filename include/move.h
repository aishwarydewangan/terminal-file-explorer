#ifndef MOVE_H
#define MOVE_H

#include "utils.h"
#include "copy.h"
#include "delete.h"

void moveFile(const char *sourceFile, const char *destinationFile);

void moveDirectory(string sourceDirectory, string destinationDirectory);

#endif