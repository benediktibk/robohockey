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
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft);
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight);
		CPPUNIT_TEST(goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsZero);
		CPPUNIT_TEST(goToStraight_startOrientationCompletelyWrong_lastRotationIsNotZero);
		CPPUNIT_TEST(goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(stop_movingSomewhere_lastMagnitudeIsZero);
		CPPUNIT_TEST(stop_movingSomewhere_lastRotationIsZero);
		CPPUNIT_TEST_SUITE_END();

	private:
		void goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed();
		void goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft();
		void goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight();
		void goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsZero();
		void goToStraight_startOrientationCompletelyWrong_lastRotationIsNotZero();
		void goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero();
		void goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero();
		void stop_movingSomewhere_lastMagnitudeIsZero();
		void stop_movingSomewhere_lastRotationIsZero();
	};
}
}
}

#endif
