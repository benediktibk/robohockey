#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELDTEST_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class DetectFieldTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DetectFieldTest);
		CPPUNIT_TEST(nextState_notCalibrated3Tries_turnAngle);
		CPPUNIT_TEST(nextState_notCalibrated1Try_NULL);
		CPPUNIT_TEST_SUITE_END();

	private:

		void nextState_notCalibrated3Tries_turnAngle();
		void nextState_notCalibrated1Try_NULL();

	};
}
}
}
}

#endif
