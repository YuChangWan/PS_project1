#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <errno.h> 
#include <fstream>
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
static ofstream log_file;


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
		//log_file << "File: COPY ----- " << fd.name << "\n";
		long handle2 = _findfirst((path2 +"\\"+ fd.name).c_str(), &fd2);
		if (handle2 == -1) {
			printf("destination dont have this files.\n");
			if (16 == fd.attrib) {
				int nResult = _mkdir( (path2 +"\\"+ fd.name).c_str() );
				log_file << "File: MAKE DIR ----- " << fd.name << "\n";
				if (nResult == -1)
				{
					printf("errorno : %d", errno);
					return;
				}
				log_file << "GOING INTO---->\n";
				reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			}
			else {
				file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
				printf("File: COPY ----- %s\n", fd.name);
				log_file << "File: COPY ----- " << fd.name << "\n" ;
			}
		}
		else if (fd.attrib == 16) {
			log_file << "DIR:  ----- " << fd.name << "\n";
			log_file << "GOING INTO---->\n";
			reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
		}
		else if (fd.time_write > fd2.time_write) {
			file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			printf("File: COPY ----- %s\n", fd.name);
			log_file << "File: COPY ----- " << fd.name << "\n";
		}
		result = _findnext(handle, &fd);
	}

	printf("GOING BACK<----\n");
	log_file << "GOING BACK<----\n";
	_findclose(handle);
	
}

void main()
{
	string path = "C:\\Users\\유창완-PC\\Desktop\\aaa";
	string path2 = "C:\\Users\\유창완-PC\\Desktop\\zzz";
	log_file.open((path2 +"\\" " mybackup.log").c_str(), ios::trunc);
	reculsive_search(path,path2);
	log_file.close();
	system("pause");
	return;
}