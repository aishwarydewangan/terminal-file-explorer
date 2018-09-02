#ifndef COPY_H
#define COPY_H

#include "utils.h"

int copyFile(const char *sourceFile, const char *destinationFile);

void index(string sourceDirectory);

int copyDirectory(string sourceDirectory, string destinationDirectory);

#endif