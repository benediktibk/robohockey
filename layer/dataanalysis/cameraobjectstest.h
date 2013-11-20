#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTSTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECTSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObjectsTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(CameraObjectsTest);
		CPPUNIT_TEST(getObjectCount_add1Object_objectCountIs1);
		CPPUNIT_TEST(getColorType_add2Objects_secondObjectIsYellow);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getObjectCount_add1Object_objectCountIs1();
		void getColorType_add2Objects_secondObjectIsYellow();
	};
}
}
}
#endif
