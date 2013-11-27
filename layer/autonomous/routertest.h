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
		CPPUNIT_TEST_SUITE_END();

	private:
		void calculateRoute_emptyField_validRoute();
		void calculateRoute_emptyField_onlyPointOfRouteIsTarget();
	};
}
}
}

#endif
