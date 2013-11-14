#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCESTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCESTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class BorderStoneDistancesTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(BorderStoneDistancesTest);
		CPPUNIT_TEST(getStandardFieldDistance_A_isCorrectDistance);
		CPPUNIT_TEST(getStandardFieldDistance_B_isCorrectDistance);
		CPPUNIT_TEST(getStandardFieldDistance_C_isCorrectDistance);
		CPPUNIT_TEST(getStandardFieldDistance_D_isCorrectDistance);
		CPPUNIT_TEST(distanceIsStandardDistance_nonStandardDistance_false);
		CPPUNIT_TEST(distanceIsStandardDistance_StandardDistance_true);
		CPPUNIT_TEST(checkForStandardDistance_fuzzyDistanceC_distanceC);
		CPPUNIT_TEST(checkForStandardDistance_nonStandardDistance_falseDistance);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getStandardFieldDistance_A_isCorrectDistance();
		void getStandardFieldDistance_B_isCorrectDistance();
		void getStandardFieldDistance_C_isCorrectDistance();
		void getStandardFieldDistance_D_isCorrectDistance();
		void distanceIsStandardDistance_nonStandardDistance_false();
		void distanceIsStandardDistance_StandardDistance_true();
		void checkForStandardDistance_fuzzyDistanceC_distanceC();
		void checkForStandardDistance_nonStandardDistance_falseDistance();

	};
}
}
}

#endif
