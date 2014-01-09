#include "common/segfaultstacktraceprinter.h"
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

using namespace RoboHockey::Common;

void handler(int sig)
{
	const size_t arraySize = 100;
	void *array[arraySize];
	size_t backtraceSize;

	// get void*'s for all entries on the stack
	backtraceSize = backtrace(array, arraySize);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, backtraceSize, STDERR_FILENO);
	exit(1);
}

SegFaultStackTracePrinter::SegFaultStackTracePrinter()
{
	signal(SIGSEGV, handler);
}

