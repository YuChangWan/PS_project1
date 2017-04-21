#include <iostream>
#include <cstdio>
using namespace std;

int main() {

	char buf[BUFSIZ];
	size_t size;

	FILE* source;
	FILE* dest;
	fopen_s(&source, "C:\\ddd\\ggg.txt", "rb");
	fopen_s(&dest, "C:\\fff\\hhh.txt", "wb");

	while (size = fread(buf, 1, BUFSIZ, source)) {
		fwrite(buf, 1, size, dest);
	}

	fclose(source);
	fclose(dest);

	return 0;
}