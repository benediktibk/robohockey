#ifndef ROBOHOCKEY_COMMON_LOGGERTEST_H
#define ROBOHOCKEY_COMMON_LOGGERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
class LoggerTest :
		public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LoggerTest);
//		CPPUNIT_TEST(write_someText_someText);
		CPPUNIT_TEST_SUITE_END();

	private:
		void write_someText_someText();
	};
}
}

#endif


