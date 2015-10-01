#pragma once

#include <crtdbg.h>

//Defining macros for program!
#ifdef _DEBUG
//For memoryLeaks detection.
#define MALLOC(SZ) _malloc_dbg((SZ), _NORMAL_BLOCK, __FILE__, __LINE__)
#define CALLOC(C, SZ) _calloc_dbg((C), (SZ), _NORMAL_BLOCK, __FILE__, __LINE__)
#define REALLOC(PTR, SZ) _realloc_dbg(PTR, SZ, _NORMAL_BLOCK, __FILE__, __LINE__)

#endif //!DEBUG