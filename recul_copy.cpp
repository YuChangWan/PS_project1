#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <errno.h> 
using namespace std;

void file_copy(string source, string dest) {
	char buf[BUFSIZ];
	size_t size;
	FILE* fsource, *fdest;

	fopen_s(&fsource, source.c_str(), "rb");
	fopen_s(&fdest, dest.c_str(), "wb");
	while (size = fread(buf, 1, BUFSIZ, fsource)) {
		fwrite(buf, 1, size, fdest);
	}
	fclose(fsource);
	fclose(fdest);
	return;
}


void reculsive_search(string path, string path2) {
	_finddata64i32_t fd,fd2;
	
	long handle = _findfirst((path + "\\*.*").c_str(), &fd);
	int result = 1;

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	result = _findnext(handle, &fd);
	result = _findnext(handle, &fd);
	printf("GOING INTO---->\n");
	while (result != -1)
	{
		printf("File: %s\n", fd.name);
		long handle2 = _findfirst((path2 +"\\"+ fd.name).c_str(), &fd2);
		if (handle2 == -1) {
			printf("destination dont have this files.\n");
			if (16 == fd.attrib) {
				int nResult = _mkdir( (path2 +"\\"+ fd.name).c_str() );
				if (nResult == 0)
				{
					printf("폴더 생성 성공");
				}
				else if (nResult == -1)
				{
					perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함\n");
					printf("errorno : %d", errno);
				}
				reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			}
			else {
				file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
				//reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			}
		}
		else if (fd.attrib == 16) {
			reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
		}
		else if (fd.attrib != fd2.attrib) {
			file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			//reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
		}
		result = _findnext(handle, &fd);
	}

	printf("GOING BACK<----\n");
	_findclose(handle);
}

void main()
{
	string path = "C:\\Users\\유창완-PC\\Desktop\\aaa";
	string path2 = "C:\\Users\\유창완-PC\\Desktop\\zzz";
	reculsive_search(path,path2);
	system("pause");
	return;
}