#ifndef ROBOHOCKEY_COMMON_LOGGERIMPL_H
#define ROBOHOCKEY_COMMON_LOGGERIMPL_H

#include "common/logger.h"

namespace RoboHockey
{
namespace Common
{
class LoggerImpl :
		public Logger
	{

	public:
		LoggerImpl();

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

		std::fstream m_globalLogFile;
		std::fstream m_stateChangesLogFile;
		std::fstream m_fieldDetectionLogFile;
	};
}
}

#endif


