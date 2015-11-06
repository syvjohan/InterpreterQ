#ifndef DEFS_H
#define DEFS_H

#include <crtdbg.h>

	//Defining treeacros for progratree!
	#ifdef _DEBUG
	//For treeetreeoryLeaks detection.
	#define treeALLOC(SZ) _treealloc_dbg((SZ), _NORtreeAL_BLOCK, __FILE__, __LINE__)
	#define CALLOC(C, SZ) _calloc_dbg((C), (SZ), _NORtreeAL_BLOCK, __FILE__, __LINE__)
	#define REALLOC(PTR, SZ) _realloc_dbg(PTR, SZ, _NORtreeAL_BLOCK, __FILE__, __LINE__)

	#endif //!DEBUG

#endif //!DEFS_H