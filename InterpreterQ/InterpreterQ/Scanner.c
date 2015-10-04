#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defs.h"

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
int numberOfInstructions = 0;

int reg[4]; // r0, r1, r2, r3

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(*A)) //Determines size of array (array / sizeof element)

int packageData(const char *str) {
	int package;
	char tmp[16];
	int len = strlen(str);
	if (str[0] == 'r') {
		memcpy(tmp, str + 1, len - 1);
		tmp[len - 1] = '\0';
		package = (short)(atoi(tmp) & 0xFFFF);
	}
	else {
		package = (short)(atoi(str) & 0xFFFF);
	}

	return package;
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

int getNumberOfFileLines(const char *path) {
	FILE *file = fopen(path, "r");
	int counter = 0;
	while (!feof(file)) {
		char ch = fgetc(file);
		if (ch == '\n') {
			++counter;
		}
	}

	fclose(file);
	return counter;
}

void readFile(const char *path) {
	FILE *file = fopen(path, "r");
	char line[64];
	numberOfInstructions = getNumberOfFileLines(path);
	instructions = (struct Instruction*)MALLOC(numberOfInstructions);

	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		if (feof(file)) {
			return; //end of file.
		}
		*(instructions + i) = parseLine(line);
		++i;
	}

	fclose(file);
}

void execute() {
	int reg0 = -1;

	int i = 0;
	do {
		reg0 = instructions[i].op0 & 0xFFFF;

		switch (instructions[i].opC.code) {
			case MOV:
				reg[reg0 & 0xFFFF] = instructions[i].op1;
				break;
			case ADD:
				reg[reg0 & 0xFFFF] += instructions[i].op1;
				break;
			case SUB:
				reg[reg0 & 0xFFFF] -= instructions[i].op1;
				break;
			case DIV:
				reg[reg0 & 0xFFFF] /= instructions[i].op1;
				break;
			case MUL:
				reg[reg0 & 0xFFFF] *= instructions[i].op1;
				break;
			case PRINT:
				printf("%i\n", reg[reg0 & 0xFFFF]);
				break;
			case CMP:

				break;
		}

		++i;
	} while (i != 32);

}

void destructor() {
	free(instructions);
	instructions = NULL;
}

void startScanning(const char *path) {
	readFile(path);
	execute();
	destructor();
}

