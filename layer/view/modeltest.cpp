#include "layer/view/modeltest.h"
#include "layer/view/model.h"

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

	model.setData(fieldObjects, false, false);

	vector<FieldObject> result = model.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void ModelTest::setData_stuckAtObstacle_stuckAtObstacle()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, true, false);

	CPPUNIT_ASSERT(model.stuckAtObstacle());
}

void ModelTest::setData_reachedTarget_reachedTarget()
{
	Model model;
	vector<FieldObject> fieldObjects;

	model.setData(fieldObjects, false, true);

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