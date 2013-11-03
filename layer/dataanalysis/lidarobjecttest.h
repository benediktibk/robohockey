#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarObjectTest);
		CPPUNIT_TEST(constructor_empty_diameterIs0);
		CPPUNIT_TEST(constructor_validPosition_positionIsSetOne);
		CPPUNIT_TEST(constructor_diameterOf5_diameterIs5);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_diameterIs0();
		void constructor_validPosition_positionIsSetOne();
		void constructor_diameterOf5_diameterIs5();
	};
}
}
}

#endif
