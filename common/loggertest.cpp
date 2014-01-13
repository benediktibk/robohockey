#include "common/loggertest.h"
#include "loggerimpl.h"

using namespace RoboHockey::Common;


void LoggerTest::write_someText_someText()
{
	LoggerImpl logger;

	logger.enableConsoleOutput();
	logger.enableLogWriting();

	logger.writeToGlobalLogFile("some Text");
	logger.writeToLogFileOfType(Logger::LogFileTypeField, "some other test.");

	CPPUNIT_ASSERT(true);
}


