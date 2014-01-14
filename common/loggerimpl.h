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
		virtual ~LoggerImpl();

		virtual void logToConsoleAndGlobalLogFile(const std::string &message);
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message);
		virtual void logToGlobalLogFile(const std::string &message);
		virtual void logToLogFileOfType(LogFileType logType, const std::string &message);

		virtual void enableConsoleOutput();
		virtual void disableConsoleOutput();
		virtual void enableLogWriting();
		virtual void disableLogWriting();

	private:
		void initLogFiles();
		void closeLogFiles();

	private:
		bool m_consoleOutputEnabled;
		bool m_logWritingEnabled;

		std::fstream m_globalLogFile;
		std::fstream m_stateChangesLogFile;
		std::fstream m_fieldLogFile;
		std::fstream m_fieldDetectionLogFile;
	};
}
}

#endif


