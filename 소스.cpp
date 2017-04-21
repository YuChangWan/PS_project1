#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <iostream>
//handle = _findfirst("C:\\Users\\Administrator\\.android\\*.*", &fd);
void reculsive_search( char* path) {
	_finddata64i32_t fd;
	char real_path[1000];
	sprintf(real_path, "%s%s", path,  "\\*.*");
	long handle = _findfirst(real_path, &fd);
	int result = 1;

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	result = _findnext(handle, &fd);
	result = _findnext(handle, &fd);

	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		if (fd.attrib == 16) {
			char next_path[1000];
			sprintf(next_path, "%s%s%s", path, "\\",fd.name);

			printf("GOING INTO---->\n");
			reculsive_search( next_path);
		}
		result = _findnext(handle, &fd);
	}
	_findclose(handle);
}

void main()
{
	char path[1000] = "C:\\Users\\Administrator\\";
	reculsive_search(path);
	system("pause");
	return;
}
