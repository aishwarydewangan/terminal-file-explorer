#include "include/rename.h"

void renameFile(const char *oldFileName, const char *newFileName) {
	if(isFileExists(oldFileName)) {
		if(!isFileExists(newFileName)) {	
			int status = rename(oldFileName, newFileName);
			if(status == 0)
				cout << "\nFile renamed successfully";
			else
				cout << "\nError: Cannot rename file. Please check for permissions!";
		} else {
			cout << "\nError: Destination File already exists. Please check name!";
		}
	} else {
		cout << "\nError: Source File not found. Please check name!";
	}
}