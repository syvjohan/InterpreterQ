#include <math.h>
#include <stdint.h>

#include "Defs.h"

size_t allocatedMemSize;
size_t availableMemSize;

struct memAddress {
	char *address;
	size_t size;
};

struct memAddress *addresses;
struct memAddress *availableAddresses;


void allocateSysMem(const size_t size) {
	allocatedMemSize = MALLOC(size);
}

size_t getSysAllocatedMem() {
	return allocatedMemSize;
}

int setAvailableMem(const size_t occupiedMem) {
	if (availableMemSize < occupiedMem) {
		return 0;
	}
	availableMemSize -= occupiedMem;
	return 1;
}

size_t getAvailableMem() {
	return availableMemSize;
}

void allocateAddressesMem(const size_t size) {
	addresses = MALLOC(size);
	availableAddresses = MALLOC(size);
}

void createAdresses(const size_t size) {
	allocateAddressesMem(size);

	char buff[6];
	char tmp[6];
	int i;
	for (i = 0; i != size; ++i) {
		sprintf(buff, "%i", i);

		//find '\0'
		int nDigits = 0;
		int j;
		for (j = 0; j != 7; ++j) {
			if (buff[j] == '\0') {
				nDigits = j;
				break;
			}
		}


		int k;
		for (k = 0; k != nDigits + 2; ++k) {
			*(tmp + 0) = '#';
			*(tmp + (k +1)) = *(buff + k);
		}

		addresses->address = tmp;

	}

	addresses->size = size;
	availableAddresses = addresses;
}

struct memAddress getAvailableAddresses() {
	return *availableAddresses;
}

int isAdressAvailable(const char *address) {
	int i;
	size_t size = availableAddresses->size;
	for (i = 0; i != size; ++i) {
		if (*(availableAddresses + i)->address == address) {
			return 1;
		}
	}
	return 0;
}
