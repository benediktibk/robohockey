#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class LidarMock;
}

namespace DataAnalysis
{
	class LidarTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarTest);
		CPPUNIT_TEST(getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance);
		CPPUNIT_TEST(getAllObjects_oneObjectInFront_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_twoObjects_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2);
		CPPUNIT_TEST(getAllObjects_objectAtLeftBorder_objectCountIs1);
		CPPUNIT_TEST(getAllObjects_objectAtRightBorder_objectCountIs1);
		CPPUNIT_TEST(getAllObjects_realWorldExample_runsThroughWithoutACrash);
		CPPUNIT_TEST(getAllObjects_objectRightOfView_positionOfOnlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_objectLeftOfView_positionOfOnlyObjectIsCorrect);
		CPPUNIT_TEST(getAllObjects_puckDirectInFront_onlyObjectIsCorrect);
		CPPUNIT_TEST(getAllobjects_oneBoundaryPostInRange_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckALittleBitDistant_diameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuck_positionAndDiameterIsCorrect);
		CPPUNIT_TEST(getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance();
		void getAllObjects_oneObjectInFront_onlyObjectIsCorrect();
		void getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect();
		void getAllObjects_twoObjects_objectCountIs2();
		void getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2();
		void getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2();
		void getAllObjects_objectAtLeftBorder_objectCountIs1();
		void getAllObjects_objectAtRightBorder_objectCountIs1();
		void getAllObjects_realWorldExample_runsThroughWithoutACrash();
		void getAllObjects_objectRightOfView_positionOfOnlyObjectIsCorrect();
		void getAllObjects_objectLeftOfView_positionOfOnlyObjectIsCorrect();
		void getAllObjects_puckDirectInFront_onlyObjectIsCorrect();
		void getAllobjects_oneBoundaryPostInRange_diameterIsCorrect();
		void getAllObjects_onePuckALittleBitDistant_diameterIsCorrect();
		void getAllObjects_onePuck_positionAndDiameterIsCorrect();
		void getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect();
	};
}
}
}

#endif
