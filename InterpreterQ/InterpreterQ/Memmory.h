#ifndef MEMMORY_H
#define MEMMORY_H

void allocateSysMem(size_t size);
size_t getSysAllocatedMem();
size_t getAvailableMem();
int setAvailableMem(size_t occupiedMem);

void createAdresses(size_t size);
char* getAvailableAddresses();
int isAdressAvailable(char *address);


#endif //!MEMMORY_H