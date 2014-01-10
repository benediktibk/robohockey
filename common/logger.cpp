#include "common/logger.h"
#include <iostream>

using namespace std;
using namespace RoboHockey::Common;

Logger::Logger() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(false),
	m_globalLogFile("log_global.txt", ios_base::out | ios_base::trunc),
	m_stateChangesLogFile("log_stateChanges.txt", ios_base::out | ios_base::trunc),
	m_fieldDetectionLogFile("log_fieldDetection.txt", ios_base::out | ios_base::trunc)
{ }

Logger::~Logger()
{ }

void Logger::logToConsole(const string &message)
{
	if (m_consoleOutputEnabled)
		cout << message << endl;
}

void Logger::logErrorToConsole(const string &message)
{
	if (m_consoleOutputEnabled)
		cerr << message << endl;
}

void Logger::writeToGlobalLogFile(const string &message)
{
	if (m_logWritingEnabled)
		m_globalLogFile << message << endl;
}

void Logger::writeToLogFileOfType(LogFileType logType, const string &message)
{
	if (m_logWritingEnabled)
	{
		switch (logType)
		{
		case LogFileTypeGlobal:
			m_globalLogFile << message << endl;
			break;

		case LogFileTypeStateChanges:
			m_stateChangesLogFile << message << endl;
			break;

		case LogFileTypeFieldDetection:
			m_fieldDetectionLogFile << message << endl;
			break;
		}
	}
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

