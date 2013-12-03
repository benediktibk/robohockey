#include "layer/view/modeltest.h"
#include "layer/view/model.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void ModelTest::constructor_empty_notStuckAtObject()
{
	Model model;

	CPPUNIT_ASSERT(!model.stuckAtObstacle());
}

void ModelTest::constructor_empty_notReachedTarget()
{
	Model model;

	CPPUNIT_ASSERT(!model.reachedTarget());
}

void ModelTest::constructor_empty_canReachTarget()
{
	Model model;

	CPPUNIT_ASSERT(!model.cantReachTarget());
}

void ModelTest::constructor_empty_puckIsNotCollected()
{
	Model model;

	CPPUNIT_ASSERT(!model.isPuckCollected());
}

void ModelTest::constructor_empty_puckIsNotCollectable()
{
	Model model;

	CPPUNIT_ASSERT(!model.isPuckCollectable());
}

void ModelTest::constructor_empty_closestPuckPositionIsNotValid()
{
	Model model;

	CPPUNIT_ASSERT(!model.isClosestPuckValid());
}

void ModelTest::constructor_empty_fieldObjectColorIsBlue()
{
	Model model;

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorBlue, model.getPuckColor());
}

void ModelTest::setData_twoFieldObjects_twoFieldObjects()
{
	Model model;
	vector<FieldObject> fieldObjects;
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, false, false, false, Point());

	vector<FieldObject> result = model.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_stuckAtObstacle_stuckAtObstacle()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, true, false, RobotPosition(), Point(), false, false, false, false, false, Point());

	CPPUNIT_ASSERT(model.stuckAtObstacle());
}

void ModelTest::setData_reachedTarget_reachedTarget()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, true, RobotPosition(), Point(), false, false, false, false, false, Point());

	CPPUNIT_ASSERT(model.reachedTarget());
}

void ModelTest::setTargetPoints_twoTargetPositions_twoTargetPositions()
{
	Model model;
	vector<Point> targetPositions;
	targetPositions.push_back(Point());
	targetPositions.push_back(Point());

	model.setTargetPoints(targetPositions);

	vector<Point> result = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_currentPosition_currentPositionIsCorrect()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, true, false, RobotPosition(Point(3, 2), 1), Point(), false, false, false, false, false, Point());

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(3, 2), 1), model.getCurrentPosition()));
}

void ModelTest::setData_cantReachTarget_cantReachTarget()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, true, false, false, false, Point());

	CPPUNIT_ASSERT(model.cantReachTarget());
}

void ModelTest::setData_puckIsCollected_puckIsCollected()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, true, false, false, Point());

	CPPUNIT_ASSERT(model.isPuckCollected());
}

void ModelTest::setData_puckIsCollectable_puckIsCollectable()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, false, true, false, Point());

	CPPUNIT_ASSERT(model.isPuckCollectable());
}

void ModelTest::setData_closestPuckPositionValid_closestPuckPositionValid()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, false, false, true, Point());

	CPPUNIT_ASSERT(model.isClosestPuckValid());
}

void ModelTest::setData_closestPuckPositionNotValid_closestPuckPositionNotValid()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, false, false, false, Point());

	CPPUNIT_ASSERT(!model.isClosestPuckValid());
}

void ModelTest::setData_closestPuckPosition5And3_closestPuckPosition5And3()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, false, RobotPosition(), Point(), false, false, false, false, true, Point(5, 3));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 3), model.getClosestPuckPosition()));
}

void ModelTest::setPuckColor_puckColorYellow_puckColorIsYellow()
{
	Model model;

	model.setPuckColor(FieldObjectColorYellow);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorYellow, model.getPuckColor());
}

void ModelTest::setPuckColor_puckColorBlue_puckColorIsBlue()
{
	Model model;

	model.setPuckColor(FieldObjectColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorBlue, model.getPuckColor());
}
