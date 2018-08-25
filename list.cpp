#include "include/list.h"

string check(unsigned const char type) {
    if(type == DT_REG)
        return "File";
    if(type == DT_DIR)
        return "Directory";
    return "None";
}

int show(const char *path) {
	struct dirent *entry;

	DIR *dp;

	dp = opendir(path);

	if (dp == NULL) {
		perror("opendir");
		return -1;
	}

	cout << "Name\t\t\t\t" << "Type\t\t\t\t" << "Size (Bytes)\t\t\t\t" << "Permissions\t\t\t\t" << "Last Modified";

	while((entry = readdir(dp))) {
		struct stat sb;
		stat(entry->d_name, &sb);
		cout << endl;
		cout << entry->d_name << "\t\t\t\t";
		cout << check(entry->d_type) << "\t\t\t\t";
		cout << sb.st_size << "\t\t\t\t";
		cout << (sb.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO)) << "\t\t\t\t";
		cout << ctime(&sb.st_mtime) << "\t\t\t\t";
    }

    closedir(dp);

    return 0;
}