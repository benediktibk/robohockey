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
		CPPUNIT_TEST(update_oneObjectFromLidarAndNoObjectFromCamera_noColor);
		CPPUNIT_TEST(update_twoObjectsFromLidarAndOneFromCamera_correctColor);
		CPPUNIT_TEST(update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor);
		CPPUNIT_TEST(tryToDetectField_noValidPattern_false);
		CPPUNIT_TEST(tryToDetectField_validPattern_true);
		CPPUNIT_TEST(tryToDetectField_noValidPattern_noTransformation);
		CPPUNIT_TEST(tryToDetectField_validPattern_transformed);
		CPPUNIT_TEST(tryToDetectField_validPattern_correctNumberOfFieldObjects);
		CPPUNIT_TEST(tryToDetectField_validPattern_correctTransformation);
		CPPUNIT_TEST(tryToDetectField_realWorldExample_positionIsCorrect);
		CPPUNIT_TEST(isPointInsideField_notCalibrated_true);
		CPPUNIT_TEST(isPointInsideField_pointIsInside_true);
		CPPUNIT_TEST(isPointInsideField_pointIsOutside_false);
		CPPUNIT_TEST(isPointInsideField_pointIsUnderField_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_noLidarObjects_noFieldObjects();
		void update_oneObjectFromLidarInView_oneObject();
		void update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject();
		void update_oneObjectFromLidarAndNoObjectFromCamera_noColor();
		void update_twoObjectsFromLidarAndOneFromCamera_correctColor();
		void update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor();
		void tryToDetectField_noValidPattern_false();
		void tryToDetectField_validPattern_true();
		void tryToDetectField_noValidPattern_noTransformation();
		void tryToDetectField_validPattern_transformed();
		void tryToDetectField_validPattern_correctNumberOfFieldObjects();
		void tryToDetectField_validPattern_correctTransformation();
		void tryToDetectField_realWorldExample_positionIsCorrect();
		void isPointInsideField_notCalibrated_true();
		void isPointInsideField_pointIsInside_true();
		void isPointInsideField_pointIsOutside_false();
		void isPointInsideField_pointIsUnderField_false();
	};
}
}
}

#endif
