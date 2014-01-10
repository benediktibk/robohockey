#include "common/loggermock.h"

using namespace RoboHockey::Common;

LoggerMock::LoggerMock()
{ }

void LoggerMock::logToConsole(const std::string &)
{
}

void LoggerMock::logErrorToConsole(const std::string &)
{
}

void LoggerMock::writeToGlobalLogFile(const std::string &)
{
}

void LoggerMock::writeToLogFileOfType(Logger::LogFileType , const std::string &)
{
}

void LoggerMock::enableConsoleOutput()
{
}

void LoggerMock::disableConsoleOutput()
{
}

void LoggerMock::enableLogWriting()
{
}

void LoggerMock::disableLogWriting()
{
}

