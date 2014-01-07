#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldObjectTest);
		CPPUNIT_TEST(constructor_validCircle_getCircleReturnsSameCircle);
		CPPUNIT_TEST(constructor_validColor_getCircleReturnsSameColor);
		CPPUNIT_TEST(constructor_validArguments_seenIs0);
		CPPUNIT_TEST(constructor_validArguments_notSeenIs0);
		CPPUNIT_TEST(constructor_validArguments_shouldBeSeenIs0);
		CPPUNIT_TEST(constructor_seenIs1_seenIs1);
		CPPUNIT_TEST(constructor_notSeenIs2_notSeenIs2);
		CPPUNIT_TEST(constructor_shouldBeSeenIs3_shouldBeSeenIs3);
		CPPUNIT_TEST(setColor_blueColor_IsBlueColor);
		CPPUNIT_TEST(setCircle_validCircle_getCircleReturnsSameCircle);
		CPPUNIT_TEST(seen_empty_seenIs1);
		CPPUNIT_TEST(seen_threeTimesCalled_seenIs3);
		CPPUNIT_TEST(seen_previouslyNotSeenCalled_notSeenIs0);
		CPPUNIT_TEST(notSeen_empty_notSeenIs1);
		CPPUNIT_TEST(notSeen_twiceCalled_notSeenIs2);
		CPPUNIT_TEST(notSeen_previouslySeenCalled_seenIs1);
		CPPUNIT_TEST(shouldBeSeen_twiceCalled_shouldBeSeenIs2);
		CPPUNIT_TEST(cantBeSeen_twiceNotSeen_notSeenIs0);
		CPPUNIT_TEST(isDefinitelyExisting_shouldBeSeenOnlyOnceAndSeen_false);
		CPPUNIT_TEST(isDefinitelyExisting_shouldBeSeenAndSeenVeryOften_true);
		CPPUNIT_TEST(isDefinitelyNotExisting_notSeenOnce_false);
		CPPUNIT_TEST(isDefinitelyNotExisting_notSeenOnceAndThenSeenAgain_false);
		CPPUNIT_TEST(isDefinitelyNotExisting_notSeenVeryOften_true);
		CPPUNIT_TEST(isDefinitelyNotExisting_shouldBeSeenVeryOftenButSeenOnlyOnce_true);
		CPPUNIT_TEST(isMaybeExisting_seenOnceAndTresholdIs4_false);
		CPPUNIT_TEST(isMaybeExisting_seenTwiceAndTresholdIs4_true);
		CPPUNIT_TEST(isHardObstacle_verySmallAndGreen_true);
		CPPUNIT_TEST(isHardObstacle_verySmallAndBlue_false);
		CPPUNIT_TEST(isHardObstacle_verySmallAndYellow_false);
		CPPUNIT_TEST(isHardObstacle_verySmallAndUnknownColor_false);
		CPPUNIT_TEST(isHardObstacle_veryBigAndGreen_true);
		CPPUNIT_TEST(isHardObstacle_veryBigAndBlue_true);
		CPPUNIT_TEST(isHardObstacle_veryBigAndYellow_true);
		CPPUNIT_TEST(isHardObstacle_veryBigAndUnkownColor_true);
		CPPUNIT_TEST(getObstacle_green_boundaryPost);
		CPPUNIT_TEST(getObstacle_blue_bluePuck);
		CPPUNIT_TEST(getObstacle_yellow_yellowPuck);
		CPPUNIT_TEST(getObstacle_smallAndUnknownColor_puckSize);
		CPPUNIT_TEST(getObstacle_big_enemyRobot);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_validCircle_getCircleReturnsSameCircle();
		void constructor_validColor_getCircleReturnsSameColor();
		void constructor_validArguments_seenIs0();
		void constructor_validArguments_notSeenIs0();
		void constructor_validArguments_shouldBeSeenIs0();
		void constructor_seenIs1_seenIs1();
		void constructor_notSeenIs2_notSeenIs2();
		void constructor_shouldBeSeenIs3_shouldBeSeenIs3();
		void setColor_blueColor_IsBlueColor();
		void setCircle_validCircle_getCircleReturnsSameCircle();
		void seen_empty_seenIs1();
		void seen_threeTimesCalled_seenIs3();
		void seen_previouslyNotSeenCalled_notSeenIs0();
		void notSeen_empty_notSeenIs1();
		void notSeen_twiceCalled_notSeenIs2();
		void notSeen_previouslySeenCalled_seenIs1();
		void shouldBeSeen_twiceCalled_shouldBeSeenIs2();
		void cantBeSeen_twiceNotSeen_notSeenIs0();
		void isDefinitelyExisting_shouldBeSeenOnlyOnceAndSeen_false();
		void isDefinitelyExisting_shouldBeSeenAndSeenVeryOften_true();
		void isDefinitelyNotExisting_notSeenOnce_false();
		void isDefinitelyNotExisting_notSeenOnceAndThenSeenAgain_false();
		void isDefinitelyNotExisting_notSeenVeryOften_true();
		void isDefinitelyNotExisting_shouldBeSeenVeryOftenButSeenOnlyOnce_true();
		void isMaybeExisting_seenOnceAndTresholdIs4_false();
		void isMaybeExisting_seenTwiceAndTresholdIs4_true();
		void isHardObstacle_verySmallAndGreen_true();
		void isHardObstacle_verySmallAndBlue_false();
		void isHardObstacle_verySmallAndYellow_false();
		void isHardObstacle_verySmallAndUnknownColor_false();
		void isHardObstacle_veryBigAndGreen_true();
		void isHardObstacle_veryBigAndBlue_true();
		void isHardObstacle_veryBigAndYellow_true();
		void isHardObstacle_veryBigAndUnkownColor_true();
		void getObstacle_green_boundaryPost();
		void getObstacle_blue_bluePuck();
		void getObstacle_yellow_yellowPuck();
		void getObstacle_smallAndUnknownColor_puckSize();
		void getObstacle_big_enemyRobot();
	};
}
}
}

#endif
