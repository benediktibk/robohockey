#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouteTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouteTest);
		CPPUNIT_TEST(constructor_empty_isNotValid);
		CPPUNIT_TEST(constructor_empty_pointCountIs0);
		CPPUNIT_TEST(addPoint_onceCalled_pointCountIs1);
		CPPUNIT_TEST(addPoint_twiceCalled_pointCountIs2);
		CPPUNIT_TEST(isValid_onePointAdded_true);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_isNotValid();
		void constructor_empty_pointCountIs0();
		void addPoint_onceCalled_pointCountIs1();
		void addPoint_twiceCalled_pointCountIs2();
		void isValid_onePointAdded_true();
	};
}
}
}

#endif
