#include "layer/dataanalysis/odometrytest.h"
#include "layer/dataanalysis/odometryimpl.h"
#include "layer/hardware/odometrymock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void OdometryTest::setCurrentPosition_mockHardwareOdometry_atLeastOneCallToSetCurrentPosition()
{
	Hardware::OdometryMock hardwareOdometry;
	OdometryImpl odometry(hardwareOdometry);

	odometry.setCurrentPosition(RobotPosition(Point(3, 4), 2));

	CPPUNIT_ASSERT(hardwareOdometry.getCallsToSetCurrentPosition() > 0);
}