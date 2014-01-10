#include "common/loggerimpl.h"
#include <iostream>

using namespace std;
using namespace RoboHockey::Common;

LoggerImpl::LoggerImpl() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(false),
	m_globalLogFile("log_global.txt", ios_base::out | ios_base::trunc),
	m_stateChangesLogFile("log_stateChanges.txt", ios_base::out | ios_base::trunc),
	m_fieldDetectionLogFile("log_fieldDetection.txt", ios_base::out | ios_base::trunc)
{ }

void LoggerImpl::logToConsole(const string &message)
{
	if (m_consoleOutputEnabled)
		cout << message << endl;
}

void LoggerImpl::logErrorToConsole(const string &message)
{
	if (m_consoleOutputEnabled)
		cerr << message << endl;
}

void LoggerImpl::writeToGlobalLogFile(const string &message)
{
	if (m_logWritingEnabled)
		m_globalLogFile << message << endl;
}

void LoggerImpl::writeToLogFileOfType(LogFileType logType, const string &message)
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

void LoggerImpl::enableConsoleOutput()
{
	m_consoleOutputEnabled = true;
}

void LoggerImpl::disableConsoleOutput()
{
	m_consoleOutputEnabled = false;
}

void LoggerImpl::enableLogWriting()
{
	m_logWritingEnabled = true;
}

void LoggerImpl::disableLogWriting()
{
	m_logWritingEnabled = false;
}

