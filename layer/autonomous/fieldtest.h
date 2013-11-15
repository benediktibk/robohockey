#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldTest:
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldTest);
		CPPUNIT_TEST(update_noLidarObjects_noFieldObjects);
		CPPUNIT_TEST(update_oneObjectFromLidarInView_oneObject);
		CPPUNIT_TEST(update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_noLidarObjects_noFieldObjects();
		void update_oneObjectFromLidarInView_oneObject();
		void update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects();
	};
}
}
}

#endif
