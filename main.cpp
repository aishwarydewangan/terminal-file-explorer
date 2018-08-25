#include "include/list.h"
#include "include/create.h"
#include "include/copy.h"
#include "include/delete.h"
#include "include/move.h"
#include "include/rename.h"
#include "include/search.h"
#include "include/snapshot.h"

int main() {

	//show("/Users/aishwary/Desktop/");

	createFile("hello.txt");
	
	//createDirectory("Hello");

	//copyFile("hello.txt", "hey.txt");

	//copyDirectory("dsa", "/Users/aishwary/Desktop/testing");

	//deleteFile("/Users/aishwary/Desktop/hello.txt");

	//deleteDirectory("");

	//moveFile("hello.txt", "hey.txt");

	//moveDirectory("dsa", "/Users/aishwary/Desktop/testing");

	renameFile("hello.txt", "hey.mp4");

	search("/Users/aishwary/Desktop", "dsa");

	snapshot("/Users/aishwary/Desktop", 0);

	return 0;
}