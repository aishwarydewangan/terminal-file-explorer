#include <cstdio>
#include <iostream>

using namespace std;

void deleteFile(const char *name) {
	if(remove(name) == 0)
		cout << "\nFile Deleted Successfully";
	else
		cout << "\nError: Cannot delete file. Please check file name!";
}

int main() {
	deleteFile("hello.txt");
	return 0;
}