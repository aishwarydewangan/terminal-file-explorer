#include "include/list.h"

vector<string> getListBuffer(const char *path) {
	struct dirent *entry;

	vector<string> v;

	DIR *dp;

	dp = opendir(path);

	if (dp == NULL) {
		perror("opendir");
	}

	while((entry = readdir(dp))) {
		string str;
		struct stat sb;
		stat(entry->d_name, &sb);
		str = entry->d_name;
		str = str + "/" + getPermissions(sb) + "/";
		str = str + getpwuid(sb.st_uid)->pw_name + "/";
		str = str + getgrgid(sb.st_gid)->gr_name + "/";
		str = str + ctime(&sb.st_mtime);
		v.push_back(str + "\0");
    }

    closedir(dp);

    return v;
}

vector<string> getDirectoryBuffer(const char *path) {
	struct dirent *entry;

	vector<string> v;

	DIR *dp;

	dp = opendir(path);

	if (dp == NULL) {
		perror("opendir");
	}

	while((entry = readdir(dp))) {
		v.push_back(entry->d_name);
    }

    closedir(dp);

    return v;
}