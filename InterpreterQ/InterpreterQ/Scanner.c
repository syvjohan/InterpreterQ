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
#define LABEL 0x0B

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
	OP_CODE(LABEL),
};

struct Instruction {
	struct OpCode opC;

	int op0;
	int op1;
};

struct Instruction *instructions;

int reg[4]; // r0, r1, r2, r3

struct Map {
	char *name;
	int index;
};

struct Map *mapLabel;

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
	return 0;
}

int exchangeLabel(char *str) {
	int i;
	for (i = 0; i != 10; ++i) {
		if (str == mapLabel[i].name) {
			return mapLabel[i].index;
		}
	}
	return -1;
}

struct Instruction parseLine(const char *line, int count) {
	char cmdStr[16];
	char op0Str[16];
	char op1Str[16];
	int len = findFirstOf(line, '\n');
	int op0 = findFirstOf(line, ' ');
	int op1 = findFirstOf(line + op0 + 1, ' ');

	memcpy(cmdStr, line, op0);
	cmdStr[op0] = '\0';

	memcpy(op0Str, line + op0 + 1, op1);
	memcpy(op1Str, line + op0 + op1 +2, -op1 - op0 -2 + len);

	op1Str[-op1 - op0 -2 + len] = '\0';	
	op0Str[op1] = '\0';

	if (strcmp(cmdStr, "JE") == 0 || strcmp(cmdStr, "JLE") == 0 || strcmp(cmdStr, "JGE") == 0) {
		memcpy(op0Str, line + op0, len - op0);
		op0Str[len - op0] = '\0';
		sprintf(op0Str, "%i", exchangeLabel(op0Str));

		*op1Str = '\0';
	}

	if (strlen(cmdStr) == 0) {
		int size = ARRAY_SIZE(mapLabel);
		memcpy(op0Str, line, len);
		op0Str[len] = '\0';
		memcpy(cmdStr, "LABEL\0", 6); 
		sprintf(op1Str, "%i", count);

		mapLabel[size].index = count;
		mapLabel[size].name = op0Str;

	} 

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

//Not used!!!
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
	char line[16];

	int i = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		if (feof(file)) {
			return; //end of file.
		}
		//Exclude empty lines.
		else if (line[0] != '\n') {
			*(instructions + i) = parseLine(line, i);
		}

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
			//Compare.
			case CMP:
				if (reg[reg0 & 0xFFFF] > instructions[i].op1) {
					reg[3] = 1;
				}
				else if (reg[reg0 & 0xFFFF] < instructions[i].op1) {
					reg[3] = -1;
				} else {
					reg[3] = 0;
				}
				break;
			//Jump Less.
			case JLE:
				if (reg[3] < 0) { i = instructions[i].op0 - 1; }
				break;
			//Junl equal.
			case JE:
				if (reg[3] == 0) { i = instructions[i].op0 - 1; }
				break;
			//Jump greater.
			case JGE:
				if (reg[3] > 1) { i = instructions[i].op0 - 1; }
				break;
		}
		++i;
	} while (i != 32);
	//exit(0); For release uncomment.
}

void destructor() {
	free(instructions);
	instructions = NULL;
}

void constructor() {
	instructions = (struct Instructor*)MALLOC(1024);
	mapLabel = (struct MapLabel*)MALLOC(10);
}

void startScanning(const char *path) {
	constructor();
	readFile(path);
	execute();
	destructor();
}

