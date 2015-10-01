#include <math.h>
#include <stdint.h>

#include "Defs.h"

size_t allocatedMemSize;
size_t availableMemSize;

struct memAddress {
	char *address;
};

struct memAddress *addresses;
struct memAddress *availableAddresses;


void allocateSysMem(size_t size) {
	allocatedMemSize = MALLOC(size);
}

size_t getSysAllocatedMem() {
	return allocatedMemSize;
}

int setAvailableMem(size_t occupiedMem) {
	if (availableMemSize < occupiedMem) {
		return 0;
	}
	availableMemSize -= occupiedMem;
	return 1;
}

size_t getAvailableMem() {
	return availableMemSize;
}

void allocateAddressesMem(size_t size) {
	addresses = MALLOC(size);
	availableAddresses = MALLOC(size);
}

void createAdresses(char *start, size_t size) {
	allocateAddressesMem(size);

	char buff[6] = "000000";
	char tmp[7] = "#000000";
	int i;
	for (i = 0; i != size; ++i) {
		sprintf(buff, "%d", i);

		//find '\0'
		int j;
		for (j = 0; j != 7; ++j) {
			if (buff[j] == '\0') {
				buff[j] = '0';
				break;
			}
		}

		tmp[6] = buff[0];
		tmp[5] = buff[1];
		tmp[4] = buff[2];
		tmp[3] = buff[3];
		tmp[2] = buff[4];
		tmp[1] = buff[5];

		addresses[i].address = tmp;
		printf("%s\n", tmp);
	}

	availableAddresses = addresses;
}

char* getAvailableAddresses() {

}

int isAdressAvailable(char *address) {

}
