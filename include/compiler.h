#include "config.h"

#if EXPORT_TO_DLL==1
#define public __declspec(dllexport)
#else
#define public
#endif