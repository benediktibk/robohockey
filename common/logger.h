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
			LogFileTypeFieldDetection,
			LogFileTypeRobot
		};

	public:
		virtual ~Logger() { }
		virtual void logToConsoleAndGlobalLogFile(const std::string &message) = 0;
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message) = 0;
		virtual void logToGlobalLogFile(const std::string &message) = 0;
		virtual void logToLogFileOfType(LogFileType logType, const std::string &message) = 0;

		virtual void enableConsoleOutput() = 0;
		virtual void disableConsoleOutput() = 0;
		virtual void enableLogWriting() = 0;
		virtual void disableLogWriting() = 0;

	};
}
}

#endif


