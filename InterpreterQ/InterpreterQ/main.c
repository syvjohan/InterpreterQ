#include <stdlib.h>
#include <stdio.h>

#include "Scanner.h"
#include "Defs.h"


int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Check for memoryLeaks.

	const char *path = "syntax/ass.asm";

	startScanning(path);

	

	system("pause");
	return 0;
}