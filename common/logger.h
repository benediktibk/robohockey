#ifndef ROBOHOCKEY_COMMON_LOGGER_H
#define ROBOHOCKEY_COMMON_LOGGER_H

#include <string>

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
			LogFileTypeFieldDetection
		};

	public:
		Logger();
		virtual void logToConsole(const std::string &message);
		virtual void logErrorToConsole(const std::string &message);
		virtual void writeToGlobalLogFile(const std::string &message);
		virtual void writeToLogFileOfType(LogFileType logType, const std::string &message);

		virtual void enableConsoleOutput();
		virtual void disableConsoleOutput();
		virtual void enableLogWriting();
		virtual void disableLogWriting();

	private:
		bool m_consoleOutputEnabled;
		bool m_logWritingEnabled;

		
	};
}
}

#endif


