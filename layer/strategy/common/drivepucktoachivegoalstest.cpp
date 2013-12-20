#include "layer/strategy/common/drivepucktoachivegoalstest.h"
#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;


void DrivePuckToAchiveGoalsTest::getColorOfTargetPucks_ownColorIsYellow_resultIsYellow()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	DrivePuckToAchiveGoals drivePuck(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, drivePuck.getColorOfTargetPucks());
}


