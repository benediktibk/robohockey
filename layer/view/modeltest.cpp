#include "layer/view/modeltest.h"
#include "layer/view/model.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

ModelTest::ModelTest() :
	m_model(0)
{ }

void ModelTest::setUp()
{
	m_callsForDataChanged = 0;
	m_model = new Model();
	connect(m_model, SIGNAL(dataForViewChanged()), this, SLOT(dataChanged()));
}

void ModelTest::tearDown()
{
	delete m_model;
}

void ModelTest::dataChanged()
{
	++m_callsForDataChanged;
}

void ModelTest::constructor_empty_notStuckAtObject()
{
	CPPUNIT_ASSERT(!m_model->stuckAtObstacle());
}

void ModelTest::constructor_empty_notReachedTarget()
{
	CPPUNIT_ASSERT(!m_model->reachedTarget());
}

void ModelTest::constructor_empty_canReachTarget()
{
	CPPUNIT_ASSERT(!m_model->cantReachTarget());
}

void ModelTest::constructor_empty_puckIsNotCollected()
{
	CPPUNIT_ASSERT(!m_model->isPuckCollected());
}

void ModelTest::constructor_empty_puckIsNotCollectable()
{
	CPPUNIT_ASSERT(!m_model->isPuckCollectable());
}

void ModelTest::constructor_empty_closestPuckPositionIsNotValid()
{
	CPPUNIT_ASSERT(!m_model->isClosestPuckValid());
}

void ModelTest::constructor_empty_fieldObjectColorIsBlue()
{
	CPPUNIT_ASSERT_EQUAL(FieldObjectColorBlue, m_model->getPuckColor());
}

void ModelTest::constructor_empty_isNotRotating()
{
	CPPUNIT_ASSERT(!m_model->isRotating());
}

void ModelTest::setData_twoFieldObjects_twoFieldObjects()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, false, Point(), false);

	vector<FieldObject> result = m_model->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_stuckAtObstacle_stuckAtObstacle()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, true, false, RobotPosition(), Point(), false, false, false, false, false, Point(), false);

	CPPUNIT_ASSERT(m_model->stuckAtObstacle());
}

void ModelTest::setData_reachedTarget_reachedTarget()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, true, RobotPosition(), Point(), false, false, false, false, false, Point(), false);

	CPPUNIT_ASSERT(m_model->reachedTarget());
}

void ModelTest::setTargetPoints_twoTargetPositions_twoTargetPositions()
{
	vector<Point> targetPositions;
	targetPositions.push_back(Point());
	targetPositions.push_back(Point());

	m_model->setTargetPoints(targetPositions);

	vector<Point> result = m_model->getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setTargetPoints_validTargetPositions_atLeastOneCallToDataChanged()
{
	vector<Point> targetPositions;
	targetPositions.push_back(Point());
	targetPositions.push_back(Point());

	m_model->setTargetPoints(targetPositions);

	CPPUNIT_ASSERT(m_callsForDataChanged > 0);
}

void ModelTest::setData_currentPosition_currentPositionIsCorrect()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, true, false, RobotPosition(Point(3, 2), 1), Point(), false, false, false, false, false, Point(), false);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(3, 2), 1), m_model->getCurrentPosition()));
}

void ModelTest::setData_cantReachTarget_cantReachTarget()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, true, false, false, false, Point(), false);

	CPPUNIT_ASSERT(m_model->cantReachTarget());
}

void ModelTest::setData_puckIsCollected_puckIsCollected()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, true, false, false, Point(), false);

	CPPUNIT_ASSERT(m_model->isPuckCollected());
}

void ModelTest::setData_puckIsCollectable_puckIsCollectable()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, true, false, Point(), false);

	CPPUNIT_ASSERT(m_model->isPuckCollectable());
}

void ModelTest::setData_closestPuckPositionValid_closestPuckPositionValid()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(), false);

	CPPUNIT_ASSERT(m_model->isClosestPuckValid());
}

void ModelTest::setData_closestPuckPositionNotValid_closestPuckPositionNotValid()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, false, Point(), false);

	CPPUNIT_ASSERT(!m_model->isClosestPuckValid());
}

void ModelTest::setData_closestPuckPosition5And3_closestPuckPosition5And3()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(5, 3), false);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 3), m_model->getClosestPuckPosition()));
}

void ModelTest::setData_isRotating_isRotating()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(5, 3), true);

	CPPUNIT_ASSERT(m_model->isRotating());
}

void ModelTest::setData_isNotRotating_isNotRotating()
{
	vector<FieldObject> fieldObjects;
    list<Point> routeList;

    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(5, 3), true);
    m_model->setData(fieldObjects, routeList, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(5, 3), false);

	CPPUNIT_ASSERT(!m_model->isRotating());
}

void ModelTest::setPuckColor_puckColorYellow_puckColorIsYellow()
{
	m_model->setPuckColor(FieldObjectColorYellow);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorYellow, m_model->getPuckColor());
}

void ModelTest::setPuckColor_puckColorBlue_puckColorIsBlue()
{
	m_model->setPuckColor(FieldObjectColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorBlue, m_model->getPuckColor());
}
