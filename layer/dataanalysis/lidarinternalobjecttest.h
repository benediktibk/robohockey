#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARINTERNALOBJECTTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARINTERNALOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarInternalObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarInternalObjectTest);
		CPPUNIT_TEST(getWidthInMeter_angleWidthIs04AndDistanceIs1_0508497647);
		CPPUNIT_TEST(getWidthInMeter_angleWidthIs0_0);
		CPPUNIT_TEST(getPositionRelativeToRobot_objectInFrontOneMeterAway_1And0);
		CPPUNIT_TEST(getPositionRelativeToRobot_objectInFrontOneMeterAwayAndCertainWidth_1254248824And0);
		CPPUNIT_TEST(getPositionRelativeToRobot_objectALittleBitRight_positionIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getWidthInMeter_angleWidthIs04AndDistanceIs1_0508497647();
		void getWidthInMeter_angleWidthIs0_0();
		void getPositionRelativeToRobot_objectInFrontOneMeterAway_1And0();
		void getPositionRelativeToRobot_objectInFrontOneMeterAwayAndCertainWidth_1254248824And0();
		void getPositionRelativeToRobot_objectALittleBitRight_positionIsCorrect();
	};
}
}
}

#endif
