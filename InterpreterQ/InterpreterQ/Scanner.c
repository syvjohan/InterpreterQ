#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defs.h"
#include "Manager.h"

#define SYSMEMALLOC 0x01
#define INCLUDE 0x02
#define $SUBROUTINE 0x03
#define ALIAS 0x04
#define PRINTV 0x05
#define PRINTA 0x06
#define WHILE 0x06
#define GOTO 0x07

#define OP_CODE(A) { A, #A }

struct OpCode {
	int code;
	const char *text;
};

struct OpCode opCodes[] = {
	OP_CODE(SYSMEMALLOC),
	OP_CODE(INCLUDE),
	OP_CODE($SUBROUTINE),
	OP_CODE(ALIAS),
	OP_CODE(PRINTV),
	OP_CODE(PRINTA),
	OP_CODE(WHILE),
	OP_CODE(GOTO),
};

struct Instruction {
	struct OpCode opC;

	int op0;
	int op1;
	int op2;
};


void searchLine(const char *line);

size_t readFirstLine(const char *path) {
	FILE *file = fopen(path, "r");
	char line[256];
	char size[6];
	char tmp[6];

	while (fgets(line, sizeof(line), file)) {
		if (strlen(line) > 1) {
			char *word = strstr(line, ":SYSMEMALLOC(");
			if (word != NULL) {
				char *close = strstr(line, ");");
				word += 12;
				int i = (word +1) - line;
				int k = close - (line);
				
				int j = 0;
				while (i != k) {
					*(tmp + 0) = line[i];
					size[j] = tmp[0];
					++j;
					++i;
				}

				*(size + j) = '\0';

				fclose(file);

				return atoi(size);

				
			}
			else {
				//Wrong start statement!
			}
			
		}
		else {
			//Line is empty!
		}
	}
	fclose(file);
	return 0;
}

void execute(struct Instruction instruction, int *counter) {

}

void readFile(const char *path) {
	//Check first line
	const size_t size = readFirstLine(path);
	if (size < 1) {
		printf("You cannot allocate less then 1 byte!");
		exit(1);
	}

	sysMemAlloc(size);

	FILE *file = fopen(path, "r");
	struct Instruction *program = MALLOC(size);
	struct Instruction tmp;
	int counter = 0;
	while (tmp.opC.code != EOF) {
		fread(&tmp, sizeof(struct Instruction), 1, file);
		program[++counter] = tmp;
	}

	//Run the program
	int i;
	for (i = 0; i != counter + 1; ++i) {
		if ((program + i)->opC.code == EOF) {
			exit(1);
		}
		else {
			execute(program[i], &i);
		}
	}

	fclose(file);


	/*char *buff = MALLOC(size);
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
	free(buff);*/
}

void searchLine(const char *line) {
	/*char tmp[20];

	int i;
	for (i = 0; i != '\n' || i != '\r'; ++i) {
		*(tmp + i) = *(line + i);
		if (memcmp(tmp, ":include", 8)) {
			include();
		}
		else if (memcmp(tmp, "$subroutine", 11)) {
			function();
		}
		else if (memcmp(tmp, "alias", 5)) {
			alias();
		}
		else if (memcmp(tmp, ":printV", 6)) {
			printV();
		} 
		else if (memcmp(tmp, ":prinA", 6)) {
			printA();
		}
		else if (memcmp(tmp, ":while", 6)) {
			WHILE();
		}
		else if (memcmp(tmp, ":goto", 5)) {
			GOTO();
		}
	}*/
}
