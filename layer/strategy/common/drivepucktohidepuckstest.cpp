#include "layer/strategy/common/drivepucktohidepuckstest.h"
#include "layer/strategy/common/drivepucktohidepucks.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;


void DrivePuckToHidePucksTest::getColorOfTargetPucks_ownColorIsYellow_resultIsBlue()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	DrivePuckToHidePucks drivePuck(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, drivePuck.getColorOfTargetPucks());
}

