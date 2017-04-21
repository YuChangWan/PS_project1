#include <stdio.h>
#include <io.h>
#include <conio.h>
#include <iostream>
#include <cstdio>
using namespace std;
void file_copy(char* source, char* dest);
void reculsive_search(char* SCpath, char* DTpath);

void main()
{
	char* source_path[1000];
	char* destination_path[1000];

	scanf("%c", source_path);                    
	scanf("%c", destination_path);

	reculsive_search(*source_path, *destination_path);
	system("pause");
	return;
}

void file_copy(char* source, char* dest) {
	_finddata64i32_t SC_fd;
	_finddata64i32_t DT_fd;

	long SC_handle = _findfirst(source, &SC_fd);         // 수정날짜 비교
	long DT_handle = _findfirst(source, &DT_fd);
	if (SC_fd.time_write > DT_fd.time_write && SC_fd.attrib == 16) {      // 해당파일이 폴더이거나 수정된 파일일 경우에 파일을 복사한다.
		char buf[BUFSIZ];
		size_t size;

		FILE* fsource;
		FILE* fdest;
		fopen_s(&fsource, source, "rb");
		fopen_s(&fdest, dest, "wb");

		while (size = fread(buf, 1, BUFSIZ, fsource)) {
			fwrite(buf, 1, size, fdest);
		}

		fclose(fsource);
		fclose(fdest);
	}
	return ;
}

void reculsive_search(char* SCpath, char* DTpath) {
	_finddata64i32_t fd;                             // 파일상태 저장하는 곳이며 소스의 path 상태만 점검하면 됨. 계속 바뀌어서 의미 그닥 없음
	char SC_real_path[1000];

	sprintf(SC_real_path, "%s%s", SCpath, "\\*.*");     // 현재 path의 모든 파일들을 SC_real_path에 저장

	long handle = _findfirst(SC_real_path, &fd);      //   위의 path를 사용할 수 있게? long으로 바꾸어 handle에 저장
	int result = 1;

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	result = _findnext(handle, &fd);					// 현재 디렉토리, 상위 디렉토리에 재귀되지 않기 위해서 next 두번 해줌
	result = _findnext(handle, &fd);

	while (result != -1)                                        // 파일목록의 끝에 다다르지 않는다면
	{
		char source_path[1000];
		char destination_path[1000];

		printf("File: %s\n", fd.name);
		sprintf(source_path, "%s%s%s", SCpath, "\\",fd.name);
		sprintf(destination_path, "%s%s%s", DTpath, "\\", fd.name);

		file_copy(source_path, destination_path);              // 파일 카피한다

		if (fd.attrib == 16) {                                 // 폴더를 발견하면 재귀함수 호출한다.
			char SC_next_path[1000];
			char DT_next_path[1000];     
			sprintf(SC_next_path, "%s%s%s", SCpath, "\\", fd.name);
			sprintf(DT_next_path, "%s%s%s", DTpath, "\\", fd.name);
			
			printf("GOING INTO---->\n");
			reculsive_search(SC_next_path, DT_next_path);
		}
		result = _findnext(handle, &fd);                       // 카피 후 path의 파일목록의 끝에 다다랐는지 확인한다.
	}
	_findclose(handle);
}

