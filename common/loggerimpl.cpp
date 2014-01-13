#include "common/loggerimpl.h"
#include <iostream>
#include <ctime>

using namespace std;
using namespace RoboHockey::Common;

LoggerImpl::LoggerImpl() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(true),
	m_globalLogFile("log_global.txt", ios_base::out | ios_base::trunc),
	m_stateChangesLogFile("log_stateChanges.txt", ios_base::out | ios_base::trunc),
	m_fieldLogFile("log_field.txt", ios_base::out | ios_base::trunc),
	m_fieldDetectionLogFile("log_fieldDetection.txt", ios_base::out | ios_base::trunc)
{
	initLogFiles();
}

LoggerImpl::~LoggerImpl()
{
	closeLogFiles();

	m_globalLogFile.close();
	m_stateChangesLogFile.close();
	m_fieldLogFile.close();
	m_fieldDetectionLogFile.close();
}

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

		case LogFileTypeField:
			m_fieldLogFile << message << endl;
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

void LoggerImpl::initLogFiles()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string timestring(buffer);

	string message = "## STARTING ROBOT\n## Starting Log: ";
	message += timestring;
	message += "\n## \n";

	for (int i = LogFileTypeGlobal; i != LogFileTypeFieldDetection; i++)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		writeToLogFileOfType(currentLogFile, message);
	}

}

void LoggerImpl::closeLogFiles()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string timestring(buffer);

	string message = "## QUITTING ROBOT\n## Closing Log: ";
	message += timestring;
	message += "\n## \n";

	for (int i = LogFileTypeGlobal; i != LogFileTypeFieldDetection; i++)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		writeToLogFileOfType(currentLogFile, message);
	}
}

