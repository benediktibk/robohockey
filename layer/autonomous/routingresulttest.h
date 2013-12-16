#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGRESULTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTINGRESULTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RoutingResultTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RoutingResultTest);
		CPPUNIT_TEST(constructor_empty_isNotValid);
		CPPUNIT_TEST(constructor_validParam_isValid);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_isNotValid();
		void constructor_validParam_isValid();
	};
	}
}
}

#endif


