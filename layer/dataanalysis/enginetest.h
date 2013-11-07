#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class EngineTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(EngineTest);
		CPPUNIT_TEST(goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed);
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeftUp);
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoRightUp_lastRotationIsRightUp);
		CPPUNIT_TEST_SUITE_END();

	private:
		void goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed();
		void goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeftUp();
		void goToStraight_lookingRightButHaveToGoRightUp_lastRotationIsRightUp();
	};
}
}
}

#endif
