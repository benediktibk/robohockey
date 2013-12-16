#ifndef ROBOHOCKEY_COMMON_SIGNUMTEST_H
#define ROBOHOCKEY_COMMON_SIGNUMTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class SignumTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(SignumTest);
		CPPUNIT_TEST(signum_4_1);
		CPPUNIT_TEST(signum_0_0);
		CPPUNIT_TEST(signum_minus3_minus1);
		CPPUNIT_TEST_SUITE_END();

	private:
		void signum_4_1();
		void signum_0_0();
		void signum_minus3_minus1();
	};
}
}

#endif
