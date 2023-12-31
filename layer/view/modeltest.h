#ifndef ROBOHOCKEY_LAYER_VIEW_MODELTEST_H
#define ROBOHOCKEY_LAYER_VIEW_MODELTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <QtCore/QObject>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Model;

	class ModelTest :
			public QObject,
			public CPPUNIT_NS::TestFixture
	{
		Q_OBJECT

		CPPUNIT_TEST_SUITE(ModelTest);
		CPPUNIT_TEST(constructor_empty_notStuckAtObject);
		CPPUNIT_TEST(constructor_empty_notReachedTarget);
		CPPUNIT_TEST(constructor_empty_canReachTarget);
		CPPUNIT_TEST(constructor_empty_puckIsNotCollected);
		CPPUNIT_TEST(constructor_empty_puckIsNotCollectable);
		CPPUNIT_TEST(constructor_empty_closestPuckPositionIsNotValid);
		CPPUNIT_TEST(constructor_empty_fieldObjectColorIsBlue);
		CPPUNIT_TEST(constructor_empty_isNotRotating);
		CPPUNIT_TEST(setData_twoFieldObjects_twoFieldObjects);
		CPPUNIT_TEST(setData_stuckAtObstacle_stuckAtObstacle);
		CPPUNIT_TEST(setData_reachedTarget_reachedTarget);
		CPPUNIT_TEST(setTargetPoints_twoTargetPositions_twoTargetPositions);
		CPPUNIT_TEST(setTargetPoints_validTargetPositions_atLeastOneCallToDataChanged);
		CPPUNIT_TEST(setData_currentPosition_currentPositionIsCorrect);
		CPPUNIT_TEST(setData_cantReachTarget_cantReachTarget);
		CPPUNIT_TEST(setData_puckIsCollected_puckIsCollected);
		CPPUNIT_TEST(setData_puckIsCollectable_puckIsCollectable);
		CPPUNIT_TEST(setData_closestPuckPositionValid_closestPuckPositionValid);
		CPPUNIT_TEST(setData_closestPuckPositionNotValid_closestPuckPositionNotValid);
		CPPUNIT_TEST(setData_closestPuckPosition5And3_closestPuckPosition5And3);
		CPPUNIT_TEST(setData_isRotating_isRotating);
		CPPUNIT_TEST(setData_isNotRotating_isNotRotating);
		CPPUNIT_TEST(setPuckColor_puckColorYellow_puckColorIsYellow);
		CPPUNIT_TEST(setPuckColor_puckColorBlue_puckColorIsBlue);
		CPPUNIT_TEST_SUITE_END();

	public:
		ModelTest();

		virtual void setUp();
		virtual void tearDown();

	private slots:
		void dataChanged();

	private:
		void constructor_empty_notStuckAtObject();
		void constructor_empty_notReachedTarget();
		void constructor_empty_canReachTarget();
		void constructor_empty_puckIsNotCollected();
		void constructor_empty_puckIsNotCollectable();
		void constructor_empty_closestPuckPositionIsNotValid();
		void constructor_empty_fieldObjectColorIsBlue();
		void constructor_empty_isNotRotating();
		void setData_twoFieldObjects_twoFieldObjects();
		void setData_stuckAtObstacle_stuckAtObstacle();
		void setData_reachedTarget_reachedTarget();
		void setTargetPoints_twoTargetPositions_twoTargetPositions();
		void setTargetPoints_validTargetPositions_atLeastOneCallToDataChanged();
		void setData_currentPosition_currentPositionIsCorrect();
		void setData_cantReachTarget_cantReachTarget();
		void setData_puckIsCollected_puckIsCollected();
		void setData_puckIsCollectable_puckIsCollectable();
		void setData_closestPuckPositionValid_closestPuckPositionValid();
		void setData_closestPuckPositionNotValid_closestPuckPositionNotValid();
		void setData_closestPuckPosition5And3_closestPuckPosition5And3();
		void setData_isRotating_isRotating();
		void setData_isNotRotating_isNotRotating();
		void setPuckColor_puckColorYellow_puckColorIsYellow();
		void setPuckColor_puckColorBlue_puckColorIsBlue();

	private:
		unsigned int m_callsForDataChanged;
		Model *m_model;
	};
}
}
}

#endif
