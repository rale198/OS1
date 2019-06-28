#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "Lock.h"
int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
#ifndef BCC_BLOCK_IGNORE
	HARD_LOCK
#endif
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
#ifndef BCC_BLOCK_IGNORE
	HARD_UNLOCK
#endif
		return res;
}
