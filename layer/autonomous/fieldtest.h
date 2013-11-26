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
		CPPUNIT_TEST(update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST(update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST(update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject);
		CPPUNIT_TEST(tryToDetectFild_noValidPattern_false);
		CPPUNIT_TEST(tryToDetectFild_validPattern_true);
		CPPUNIT_TEST(tryToDetectFild_noValidPattern_noTransformation);
		CPPUNIT_TEST(tryToDetectFild_validPattern_transformed);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_noLidarObjects_noFieldObjects();
		void update_oneObjectFromLidarInView_oneObject();
		void update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject();
		void tryToDetectFild_noValidPattern_false();
		void tryToDetectFild_validPattern_true();
		void tryToDetectFild_noValidPattern_noTransformation();
		void tryToDetectFild_validPattern_transformed();
	};
}
}
}

#endif
