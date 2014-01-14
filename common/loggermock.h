#ifndef ROBOHOCKEY_COMMON_LOGGERMOCK_H
#define ROBOHOCKEY_COMMON_LOGGERMOCK_H

#include "common/logger.h"

namespace RoboHockey
{
namespace Common
{
class LoggerMock :
		public Logger
	{
	public:
		LoggerMock();

		virtual void logToConsoleAndGlobalLogFile(const std::string &message);
		virtual void logErrorToConsoleAndWriteToGlobalLogFile(const std::string &message);
		virtual void writeToGlobalLogFile(const std::string &message);
		virtual void writeToLogFileOfType(LogFileType logType, const std::string &message);

		virtual void enableConsoleOutput();
		virtual void disableConsoleOutput();
		virtual void enableLogWriting();
		virtual void disableLogWriting();
		
	};
}
}

#endif


