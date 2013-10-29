#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class EngineTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(EngineTest);
	CPPUNIT_TEST(setSpeed_mockHardwareEngine_atLeastOneCallToSetSpeed);
	CPPUNIT_TEST_SUITE_END();

private:
	void setSpeed_mockHardwareEngine_atLeastOneCallToSetSpeed();
};
}
}
}

#endif
