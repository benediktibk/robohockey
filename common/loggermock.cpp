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

