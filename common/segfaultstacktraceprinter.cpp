#include "common/segfaultstacktraceprinter.h"
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>

using namespace RoboHockey::Common;
using namespace std;

void splitUp(const string &line, string &binary, string &file, string &offset)
{
	size_t openingRoundBracket = line.find_first_of('(');
	size_t closingRoundBracket = line.find_first_of(')');
	size_t openingSquareBracket = line.find_first_of('[');
	size_t closingSquareBracket = line.find_first_of(']');

	binary = line.substr(0, openingRoundBracket);
	file = line.substr(openingRoundBracket + 1, closingRoundBracket - openingRoundBracket - 1);
	offset = line.substr(openingSquareBracket + 1, closingSquareBracket - openingSquareBracket - 1);
}

void handler(int signal)
{
	const size_t maxStackSize = 100;
	void *array[maxStackSize];
	size_t backtraceSize = backtrace(array, maxStackSize);

	cerr << "error signal " << signal << endl;
	char **charArray = backtrace_symbols(array, backtraceSize);
	vector<string> lines;
	lines.reserve(backtraceSize);

	for (size_t i = 0; i < backtraceSize; ++i)
		lines.push_back(charArray[i]);

	delete[] charArray;

	for (vector<string>::const_iterator i = lines.begin(); i != lines.end(); ++i)
	{
		string binary;
		string file;
		string offset;
		splitUp(*i, binary, file, offset);
		cout << binary << " - " << file << " - " << offset << endl;
	}

	exit(1);
}

SegFaultStackTracePrinter::SegFaultStackTracePrinter()
{
	signal(SIGSEGV, handler);
}