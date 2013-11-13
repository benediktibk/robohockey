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

void ModelTest::setData_twoFieldObjects_twoFieldObjects()
{
	Model model;
	vector<FieldObject> fieldObjects;
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));
	fieldObjects.push_back(FieldObject(Circle(), FieldObjectColorUnknown));

	model.setData(fieldObjects, false, false, Point());

	vector<FieldObject> result = model.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_stuckAtObstacle_stuckAtObstacle()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, true, false, Point());

	CPPUNIT_ASSERT(model.stuckAtObstacle());
}

void ModelTest::setData_reachedTarget_reachedTarget()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, true, Point());

	CPPUNIT_ASSERT(model.reachedTarget());
}

void ModelTest::setData_twoTargetPositions_twoTargetPositions()
{
	Model model;
	vector<Point> targetPositions;
	targetPositions.push_back(Point());
	targetPositions.push_back(Point());

	model.setData(targetPositions);

	vector<Point> result = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_currentPosition_currentPositionIsCorrect()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, true, false, Point(3, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 2), model.getCurrentPosition()));
}
