#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defs.h"
#include "Manager.h"

void searchLine(char *line);
int countCharacters(char *lines);
void searchLine(char *line);

void readFile(const char *path) {
	char *buff = malloc(1024);
	size_t lineLen = 0;
	FILE *file = fopen(path, "r");
	char line[256];

	while (fgets(line, sizeof(line), file)) {
		if (strlen(line) != 1) {
			searchLine(line);
		}
	}

	printf("%s\n", line);


	fclose(file);
}

void searchLine(char *line) {
	char c;
	char tmp[20];
	int len = countCharacters(line);
	int i;
	for (i = 0; i != len; ++i) {
		*(tmp + i) = *(line + i);
		if (memcmp(tmp, ":SYSMEMALLOC", 12) == 0) {
			sysMemAlloc("000000", 512);
		}
		else if (memcmp(tmp, ":include", 8)) {
			include();
		}
		else if (memcmp(tmp, ".function", 9)) {
			function();
		}
		else if (memcmp(tmp, "alias", 5)) {
			alias();
		}
		else if (memcmp(tmp, ":print", 6)) {
			print();
		} 
		else if (memcmp(tmp, ":do", 3)) {
			DO();
		}
		else if (memcmp(tmp, ":while", 6)) {
			WHILE();
		}
	}
}

int countCharacters(char *line) {
	int count = 0;
	int i;
	for (i = 0; line[i] != EOF; ++i) {
		++count;
	}
	return count;
}
