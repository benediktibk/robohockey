#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouterTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterTest);
		CPPUNIT_TEST(calculateRoute_emptyField_validRoute);
		CPPUNIT_TEST(calculateRoute_emptyField_onlyPointOfRouteIsTarget);
		CPPUNIT_TEST(calculateRoute_emptyField_routeHasSameWidthAsRobot);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus0p25);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And2p25);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p1767And0p8232);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p8232And1p1767);
		CPPUNIT_TEST_SUITE_END();

	private:
		void calculateRoute_emptyField_validRoute();
		void calculateRoute_emptyField_onlyPointOfRouteIsTarget();
		void calculateRoute_emptyField_routeHasSameWidthAsRobot();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus0p25();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And2p25();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p1767And0p8232();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p8232And1p1767();
	};
}
}
}

#endif
