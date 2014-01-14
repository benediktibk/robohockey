#include "common/loggermock.h"

using namespace RoboHockey::Common;

LoggerMock::LoggerMock()
{ }

void LoggerMock::logToConsoleAndGlobalLogFile(const std::string &)
{
}

void LoggerMock::logErrorToConsoleAndWriteToGlobalLogFile(const std::string &)
{
}

void LoggerMock::logToGlobalLogFile(const std::string &)
{
}

void LoggerMock::logToLogFileOfType(Logger::LogFileType , const std::string &)
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

