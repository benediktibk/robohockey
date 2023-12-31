#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CameraObjectTest);
		CPPUNIT_TEST(getColorType_ColorTypeYellowGoal);
		CPPUNIT_TEST(getPosition_positionIs0And0);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getColorType_ColorTypeYellowGoal();
		void getPosition_positionIs0And0();

	};
}
}
}

#endif // CAMERAOBJECTTEST_H
