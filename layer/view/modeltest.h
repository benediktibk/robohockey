#ifndef ROBOHOCKEY_LAYER_VIEW_MODELTEST_H
#define ROBOHOCKEY_LAYER_VIEW_MODELTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class ModelTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(ModelTest);
		CPPUNIT_TEST(constructor_empty_notStuckAtObject);
		CPPUNIT_TEST(constructor_empty_notReachedTarget);
		CPPUNIT_TEST(constructor_empty_canReachTarget);
		CPPUNIT_TEST(setData_twoFieldObjects_twoFieldObjects);
		CPPUNIT_TEST(setData_stuckAtObstacle_stuckAtObstacle);
		CPPUNIT_TEST(setData_reachedTarget_reachedTarget);
		CPPUNIT_TEST(setData_twoTargetPositions_twoTargetPositions);
		CPPUNIT_TEST(setData_currentPosition_currentPositionIsCorrect);
		CPPUNIT_TEST(setData_cantReachTarget_cantReachTarget);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_empty_notStuckAtObject();
		void constructor_empty_notReachedTarget();
		void constructor_empty_canReachTarget();
		void setData_twoFieldObjects_twoFieldObjects();
		void setData_stuckAtObstacle_stuckAtObstacle();
		void setData_reachedTarget_reachedTarget();
		void setData_twoTargetPositions_twoTargetPositions();
		void setData_currentPosition_currentPositionIsCorrect();
		void setData_cantReachTarget_cantReachTarget();
	};
}
}
}

#endif
