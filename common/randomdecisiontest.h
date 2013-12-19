#ifndef ROBOHOCKEY_COMMON_RANDOMDECISIONTEST_H
#define ROBOHOCKEY_COMMON_RANDOMDECISIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
class RandomDecisionTest :
		public CPPUNIT_NS::TestFixture
{
	 CPPUNIT_TEST_SUITE(RandomDecisionTest);
	 CPPUNIT_TEST(decide_possibility0_false);
	 CPPUNIT_TEST(decide_possibility1_true);
	 CPPUNIT_TEST(decide_called1000TimesAndPossibilityAHalf_around500TimesTrue);
	 CPPUNIT_TEST_SUITE_END();

private:
	 void decide_possibility0_false();
	 void decide_possibility1_true();
	 void decide_called1000TimesAndPossibilityAHalf_around500TimesTrue();
};
}
}

#endif
