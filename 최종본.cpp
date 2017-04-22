#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <errno.h> 
#include <fstream>
using namespace std;

void file_copy(string source_path, string dest_path) {
	ifstream fsource(source_path, ios::binary);
	ofstream fdest(dest_path, ios::binary);

	fdest << fsource.rdbuf();

	fsource.close();
	fdest.close();

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
	
	while (result != -1)
	{
		long handle2 = _findfirst((path2 +"\\"+ fd.name).c_str(), &fd2);
		if (handle2 == -1) {
			if (16 == fd.attrib) {
				int nResult = _mkdir( (path2 +"\\"+ fd.name).c_str() );
				log_file << "MAKE DIR : " << path2 + "\\" + fd.name << "\n";

				if (nResult == -1){	printf("errorno : %d", errno);return;}

				log_file << "      cd : " << path2 + "\\" + fd.name << "\n";
				reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			}
			else {
				file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
				log_file << "OVERWRITE: " << path2 + "\\" + fd.name << "\n";
			}
		}
		else if (fd.attrib == 16) {
			log_file << "      cd : " << path2 + "\\" + fd.name << "\n";
			reculsive_search((path + "\\" + fd.name), (path2 + "\\" + fd.name));
		}
		else if (fd.time_write > fd2.time_write) {
			file_copy((path + "\\" + fd.name), (path2 + "\\" + fd.name));
			log_file << "OVERWRITE: " << path2 + "\\" + fd.name << "\n";
		}
		result = _findnext(handle, &fd);
	}
	log_file << "      cd : ..\n";
	_findclose(handle);
	
}

int main(int argc, char* argv[])
{
	if (argc != 3)return -1;
	string path = argv[1];
	string path2 = argv[2];

	//string path = "C:\\Users\\유창완-PC\\Desktop\\aaa";
	//string path2 = "C:\\Users\\유창완-PC\\Desktop\\zzz";
	log_file.open((path2 +"\\" " mybackup.log").c_str(), ios::trunc);
	reculsive_search(path,path2);
	log_file.close();
	system("pause");
	return 0;
}