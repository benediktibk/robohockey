#include "common/loggerimpl.h"
#include <iostream>
#include <ctime>
#include <boost/filesystem.hpp>
#include <assert.h>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace boost;
using namespace RoboHockey::Common;

LoggerImpl::LoggerImpl() :
	m_consoleOutputEnabled(true),
	m_logWritingEnabled(true)
{
	string folder = "log";

	for (int i = 0; i <= 999; ++i)
	{
		stringstream currentStringStream;
		currentStringStream << folder << setw(3) << setfill('0') << i ;

		if(!filesystem::exists(currentStringStream.str()))
		{
			filesystem::create_directory(currentStringStream.str());
			folder = currentStringStream.str();
			break;
		}

	}

	string globalLogFile = folder;
	globalLogFile.append("/0_global.txt");

	string stateChangesLogFile = folder;
	stateChangesLogFile.append("/1_stateChanges.txt");

	string fieldLogFile = folder;
	fieldLogFile.append("/2_field.txt");

	string fieldDetectionLogFile = folder;
	fieldDetectionLogFile.append("/3_fieldDetection.txt");

	m_globalLogFile.open(globalLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_stateChangesLogFile.open(stateChangesLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_fieldLogFile.open(fieldLogFile.c_str(), ios_base::out | ios_base::trunc);
	m_fieldDetectionLogFile.open(fieldDetectionLogFile.c_str(), ios_base::out | ios_base::trunc);


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

void LoggerImpl::logToConsoleAndGlobalLogFile(const string &message)
{
	if (m_consoleOutputEnabled)
		cout << message << endl;
	writeToGlobalLogFile(message);
}

void LoggerImpl::logErrorToConsoleAndWriteToGlobalLogFile(const string &message)
{
	if (m_consoleOutputEnabled)
		cerr << message << endl;
	writeToGlobalLogFile(message);
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

	string message;
	message += "## Starting Log: ";
	message += timestring;
	message += "\n## STARTING ROBOT\n##\n";

	for (int i = LogFileTypeGlobal; i <= LogFileTypeFieldDetection; i++)
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

	string message;
	message += "\n## \n";
	message += "## QUITTING ROBOT\n## Closing Log: ";
	message += timestring;

	for (int i = LogFileTypeGlobal; i <= LogFileTypeFieldDetection; ++i)
	{
		LogFileType currentLogFile = static_cast<LogFileType>(i);
		writeToLogFileOfType(currentLogFile, message);
	}
}

