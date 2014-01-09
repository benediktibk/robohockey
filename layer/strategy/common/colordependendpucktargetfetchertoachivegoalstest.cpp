#include "layer/strategy/common/colordependendpucktargetfetchertoachivegoalstest.h"
#include "layer/strategy/common/colordependendpucktargetfetchertoachivegoals.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"
#include <vector>

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

void ColorDependendPuckTargetFetcherToAchiveGoalsTest::getColorOfTargetPucks_ownColorIsYellow_resultIsYellow()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	ColorDependendPuckTargetFetcherToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, drivePuck.getColorOfTargetPucks());
}

void ColorDependendPuckTargetFetcherToAchiveGoalsTest::getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown, 2));
	field.setFieldObjects(objects);
	ColorDependendPuckTargetFetcherToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, drivePuck.getNumberOfKnownPucksNotInTarget());
}

void ColorDependendPuckTargetFetcherToAchiveGoalsTest::getNumberOfKnownPucksNotInTarget_threePucksOneInGoal_resultIs2()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown, 2));
	objects.push_back(FieldObject(Circle(Point(1,2), 0.2), FieldColorUnknown, 2));
	objects.push_back(FieldObject(Circle(Point(2,1), 0.2), FieldColorUnknown, 2));
	field.setFieldObjects(objects);
	field.setAchievedGoals(1);
	ColorDependendPuckTargetFetcherToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, drivePuck.getNumberOfKnownPucksNotInTarget());
}


