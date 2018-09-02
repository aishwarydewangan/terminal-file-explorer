#include "include/rename.h"

void renameFile(const char *oldFileName, const char *newFileName) {
	if(isFileExists(oldFileName)) {
		if(!isFileExists(newFileName)) {	
			int status = rename(oldFileName, newFileName);
			if(status == 0){
				printStatus("Success: File renamed successfully.");
			}
			else{
				printStatus("Error: Cannot rename file. Please check for permissions.");
			}
		} else {
			printStatus("Error: Destination File already exists. Please check name.");
		}
	} else {
		printStatus("Error: Source File not found. Please check name.");
	}
}