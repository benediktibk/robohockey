#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void LidarTest::getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	lidar.getAllObjects();

	CPPUNIT_ASSERT(hardwareLidar.getCallsToGetDistance() > 0);
}
