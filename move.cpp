#include "include/move.h"

static vector<string> filePaths, directoryPaths;

void moveFile(const char *sourceFile, const char *destinationFile) {

	printf("\e[26;1H");
	printf("\e[K");

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

			printf("\e[26;1H");
			printf("\e[K");

			printf("\e[26;1HSuccess: File moved.");
		} else {
			printf("\e[26;1HError: Destination File already exists. Please check name.");
		}
	} else {
		printf("\e[26;1HError: Source File not found. Please check name.");
	}
}

void moveDirectory(string sourceDirectory, string destinationDirectory) {

	printf("\e[26;1H");
	printf("\e[K");

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

				printf("\e[26;1H");
				printf("\e[K");

				printf("\e[26;1HSuccess: File moved.");
			} else {
				printf("\e[26;1HError: Destination Directory exists. Please check name.");
			}
		} else {
			printf("\e[26;1HError: Destination Directory does not exists. Please check name.");
		}
	} else {
		printf("\e[26;1HError: Source Directory does not exists. Please check name.");
	}
}