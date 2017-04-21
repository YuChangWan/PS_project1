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

	long SC_handle = _findfirst(source, &SC_fd);         // ������¥ ��
	long DT_handle = _findfirst(source, &DT_fd);
	if (SC_fd.time_write > DT_fd.time_write && SC_fd.attrib == 16) {      // �ش������� �����̰ų� ������ ������ ��쿡 ������ �����Ѵ�.
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
	_finddata64i32_t fd;                             // ���ϻ��� �����ϴ� ���̸� �ҽ��� path ���¸� �����ϸ� ��. ��� �ٲ� �ǹ� �״� ����
	char SC_real_path[1000];

	sprintf(SC_real_path, "%s%s", SCpath, "\\*.*");     // ���� path�� ��� ���ϵ��� SC_real_path�� ����

	long handle = _findfirst(SC_real_path, &fd);      //   ���� path�� ����� �� �ְ�? long���� �ٲپ� handle�� ����
	int result = 1;

	if (handle == -1) {
		printf("There were no files.\n");
		return;
	}

	result = _findnext(handle, &fd);					// ���� ���丮, ���� ���丮�� ��͵��� �ʱ� ���ؼ� next �ι� ����
	result = _findnext(handle, &fd);

	while (result != -1)                                        // ���ϸ���� ���� �ٴٸ��� �ʴ´ٸ�
	{
		char source_path[1000];
		char destination_path[1000];

		printf("File: %s\n", fd.name);
		sprintf(source_path, "%s%s%s", SCpath, "\\",fd.name);
		sprintf(destination_path, "%s%s%s", DTpath, "\\", fd.name);

		file_copy(source_path, destination_path);              // ���� ī���Ѵ�

		if (fd.attrib == 16) {                                 // ������ �߰��ϸ� ����Լ� ȣ���Ѵ�.
			char SC_next_path[1000];
			char DT_next_path[1000];     
			sprintf(SC_next_path, "%s%s%s", SCpath, "\\", fd.name);
			sprintf(DT_next_path, "%s%s%s", DTpath, "\\", fd.name);
			
			printf("GOING INTO---->\n");
			reculsive_search(SC_next_path, DT_next_path);
		}
		result = _findnext(handle, &fd);                       // ī�� �� path�� ���ϸ���� ���� �ٴٶ����� Ȯ���Ѵ�.
	}
	_findclose(handle);
}

