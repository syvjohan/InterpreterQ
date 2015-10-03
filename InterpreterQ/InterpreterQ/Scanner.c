#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defs.h"
#include "Manager.h"

#define MOV 0x01
#define ADD 0x02
#define SUB 0x03
#define MUL 0x04
#define DIV 0x05
#define PRINT 0x06
#define CMP 0x07
#define JLE 0x08
#define JE 0x09
#define JGE 0x0A

#define OP_CODE(A) { A, #A }

struct OpCode {
	int code;
	const char *text;
};

struct OpCode opCodes[] = {
	OP_CODE(MOV), // { MOV, "MOV" }
	OP_CODE(ADD),
	OP_CODE(SUB),
	OP_CODE(MUL),
	OP_CODE(DIV),
	OP_CODE(PRINT),
	OP_CODE(CMP),
	OP_CODE(JLE),
	OP_CODE(JE),
	OP_CODE(JGE),
};

struct Instruction {
	struct OpCode opC;

	int op0;
	int op1;
};

struct Instruction *instructions;

struct Register {
	void *value;
	char *name;
};

struct Register *reg;

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A)) //Determines size of array (array / sizeof element)

struct Instruction parseLine(const char *line) {
	char cmdStr[16];
	char op0Str[16];
	char op1Str[16];
	int len = findFirstOf(line, '\n');
	int op0 = findFirstOf(line, ' ');
	int op1 = findFirstOf(line + op0 + 1, ' ');

	memcpy(cmdStr, line, op0);
	cmdStr[op0] = '\0';

	memcpy(op0Str, line + op0 + 1, op1);
	op0Str[op1] = '\0';

	memcpy(op1Str, line + op0 + op1 + 2, -op1 - op0 - 2 + len);
	op1Str[-op1 - op0 - 2 + len] = '\0';

	struct Instruction instruct;
	instruct.op0 = packageData(op0Str);
	instruct.op1 = packageData(op1Str);
	instruct.opC.text = cmdStr;

	//set instruct.opC.code
	int i;
	for (i = 0; i < ARRAY_SIZE(opCodes); ++i) {
		if (strcmp(cmdStr, opCodes[i].text) == 0) {
			instruct.opC = opCodes[i];
			break;
		}
	}

	return instruct;
}

int packageData(const char *str) {
	int package;
	char tmp[16];
	int len = strlen(str);
	if (str[0] == 'r') {
		memcpy(tmp, str + 1, len - 1);
		tmp[len -1] = '\0';
		package = (short)(atoi(tmp) & 0xFFFF);
	}
	else {
		package = (short)(atoi(str) & 0xFFFF);
	}
	
	return package;
}

void readFile(const char *path) {
	FILE *file = fopen(path, "r");
	char line[64];
	instructions = (char*)MALLOC(32);
	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		if (feof(file)) {
			return; //end of file.
		}
		*(instructions + i) = parseLine(line);
		++i;
	}

}

int findFirstOf(const char *cStr, char ch) {
	int len = strlen(cStr);
	int i;

	for (i = 0; i != len; ++i) {
		if (*(cStr + i) == ch) {
			return i;
		}
	}
	return -1;
}


void insertIntoRegister(void *value, const char regName) {
	int i;
	for (i = 0; i < ARRAY_SIZE(reg); ++i) {
		if (strcmp(regName, reg[i].name) == 0) {
			reg[i].value = value;
			return;
		}
			
	}
	//TODO insert value and name into reg!!
	reg[ARRAY_SIZE(reg) + 1].name = regName;
	reg[ARRAY_SIZE(reg) + 1].value = value;
}

void execute() {
	int i = 0;
	do {
		switch (instructions[i].opC.code) {
		case MOV:
			insertIntoRegister(instructions[i].op1, instructions[i].op0);
			
			break;

		case ADD:
			insertIntoRegister(instructions[i].op1, instructions[i].op0);

			break;

		case PRINT:
			insertIntoRegister(instructions[i].op1, instructions[i].op0);

			break;
		}


	} while (i != 32);

}

void startScanning(const char *path) {
	readFile(path);
	execute();
}

void destructor() {
	free(instructions);
	instructions = NULL;
}

/*void searchLine(const char *line);

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
	struct Instruction tmp = { .op0 = 0, .op1 = 0 };
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
	free(buff);
}

void searchLine(const char *line) {
	char tmp[20];

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
	}
}
*/