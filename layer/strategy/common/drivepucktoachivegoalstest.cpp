#include "layer/strategy/common/drivepucktoachivegoalstest.h"
#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"
#include <vector>

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

void DrivePuckToAchiveGoalsTest::getColorOfTargetPucks_ownColorIsYellow_resultIsYellow()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	DrivePuckToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, drivePuck.getColorOfTargetPucks());
}

void DrivePuckToAchiveGoalsTest::getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown));
	field.setFieldObjects(objects);
	DrivePuckToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, drivePuck.getNumberOfKnownPucksNotInTarget());
}

void DrivePuckToAchiveGoalsTest::getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown));
	objects.push_back(FieldObject(Circle(Point(1,2), 0.2), FieldColorUnknown));
	objects.push_back(FieldObject(Circle(Point(2,1), 0.2), FieldColorUnknown));
	field.setFieldObjects(objects);
	field.setAchievedGoals(1);
	DrivePuckToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, drivePuck.getNumberOfKnownPucksNotInTarget());
}


