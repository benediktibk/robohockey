#include "common/logger.h"
#include <iostream>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Common::Logger;

Logger::Logger() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(false)
{ }

void Logger::logToConsole(const string &message)
{
}

void Logger::logErrorToConsole(const string &message)
{
}

void Logger::writeToGlobalLogFile(const string &message)
{
}

void Logger::writeToLogFileOfType(LogFileType logType, const string &message)
{
}

void Logger::enableConsoleOutput()
{
	m_consoleOutputEnabled = true;
}

void Logger::disableConsoleOutput()
{
	m_consoleOutputEnabled = false;
}

void Logger::enableLogWriting()
{
	m_logWritingEnabled = true;
}

void Logger::disableLogWriting()
{
	m_logWritingEnabled = false;
}

