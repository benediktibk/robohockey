#include "layer/strategy/common/drivepucktohidepuckstest.h"
#include "layer/strategy/common/drivepucktohidepucks.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"
#include <vector>

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

void DrivePuckToHidePucksTest::getColorOfTargetPucks_ownColorIsYellow_resultIsBlue()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	DrivePuckToHidePucks drivePuck(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, drivePuck.getColorOfTargetPucks());
}

void DrivePuckToHidePucksTest::getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown));
	field.setFieldObjects(objects);
	DrivePuckToHidePucks drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, drivePuck.getNumberOfKnownPucksNotInTarget());
}

void DrivePuckToHidePucksTest::getNumberOfKnownPucksNotInTarget_threePucksOnePuckHidden_resultIs2()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown));
	objects.push_back(FieldObject(Circle(Point(1,2), 0.2), FieldColorUnknown));
	objects.push_back(FieldObject(Circle(Point(2,1), 0.2), FieldColorUnknown));
	field.setFieldObjects(objects);
	field.setEnemyHiddenPucks(1);
	DrivePuckToHidePucks drivePuck(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, drivePuck.getNumberOfKnownPucksNotInTarget());
}

