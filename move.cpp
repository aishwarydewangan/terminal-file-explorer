#include "include/move.h"

static vector<string> filePaths, directoryPaths;

int moveFile(const char *sourceFile, const char *destinationFile) {
	if(isFileExists(sourceFile)) {
		if(!isFileExists(destinationFile)) {	
			char buf[BUFSIZ];
		    size_t size;

		    int source = open(sourceFile, O_RDONLY, 0);
		    int dest = open(destinationFile, O_WRONLY | O_CREAT , 0644);

		    while ((size = read(source, buf, BUFSIZ)) > 0) {
		        write(dest, buf, size);
		    }

		    close(source);
		    close(dest);

			deleteFile(sourceFile);

		} else {
			//Error: Destination File already exists. Please check name!
			return -1;
		}
	} else {
		//Error: Source File not found. Please check name!
		return -2;
	}
	return 1;
}

int moveDirectory(string sourceDirectory, string destinationDirectory) {

	if(isDirectoryExists(sourceDirectory.c_str())) {
		if(isDirectoryExists(destinationDirectory.c_str())) {
			string sourceAbsolutePath(realpath(sourceDirectory.c_str(), NULL));

			string destinationAbsolutePath(realpath(destinationDirectory.c_str(), NULL));

			int pos = sourceAbsolutePath.find_last_of('/');

			string sourceName = sourceAbsolutePath.substr(pos+1);

			index(realpath(sourceDirectory.c_str(), NULL));

			string home(destinationAbsolutePath + '/' + sourceName);

			if(!isDirectoryExists(home.c_str())) {
				mkdir(home.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

				for(int i = 0; i < directoryPaths.size(); i++) {
					string temp = destinationAbsolutePath + directoryPaths[i].substr(pos);
					mkdir(temp.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
				}

				for(int i = 0; i < filePaths.size(); i++) {
					string temp = destinationAbsolutePath + filePaths[i].substr(pos);
					copyFile(filePaths[i].c_str(), temp.c_str());
				}

				deleteDirectory(sourceAbsolutePath.c_str());
			} else {
				//Error: Destination Directory Exists. Please check name!
				return -1;
			}
		} else {
			//Error: Move to Directory does not exists.
			return -2;
		}
	} else {
		//Error: Move from Directory does not exists. 
		return -3;
	}
	return 1;
}