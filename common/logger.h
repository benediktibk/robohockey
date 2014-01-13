#ifndef ROBOHOCKEY_COMMON_LOGGER_H
#define ROBOHOCKEY_COMMON_LOGGER_H

#include <string>
#include <fstream>

namespace RoboHockey
{
namespace Common
{
class Logger
	{
	public:
		enum LogFileType
		{
			LogFileTypeGlobal,
			LogFileTypeStateChanges,
			LogFileTypeField,
			LogFileTypeFieldDetection
		};

	public:

		virtual void logToConsole(const std::string &message) = 0;
		virtual void logErrorToConsole(const std::string &message) = 0;
		virtual void writeToGlobalLogFile(const std::string &message) = 0;
		virtual void writeToLogFileOfType(LogFileType logType, const std::string &message) = 0;

		virtual void enableConsoleOutput() = 0;
		virtual void disableConsoleOutput() = 0;
		virtual void enableLogWriting() = 0;
		virtual void disableLogWriting() = 0;

	};
}
}

#endif


