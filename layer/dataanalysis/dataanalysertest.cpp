#include "layer/dataanalysis/dataanalysertest.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetSonar()
{
	Hardware::RobotMock *robot = new Hardware::RobotMock();
	DataAnalyserImpl *dataAnalyser = new DataAnalyserImpl(robot);

	CPPUNIT_ASSERT(robot->getCallsToGetSonar() > 0);
	delete dataAnalyser;
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetLidar()
{
	Hardware::RobotMock *robot = new Hardware::RobotMock();
	DataAnalyserImpl *dataAnalyser = new DataAnalyserImpl(robot);

	CPPUNIT_ASSERT(robot->getCallsToGetLidar() > 0);
	delete dataAnalyser;
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetCamera()
{
	Hardware::RobotMock *robot = new Hardware::RobotMock();
	DataAnalyserImpl *dataAnalyser = new DataAnalyserImpl(robot);

	CPPUNIT_ASSERT(robot->getCallsToGetCamera() > 0);
	delete dataAnalyser;
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetOdometry()
{
	Hardware::RobotMock *robot = new Hardware::RobotMock();
	DataAnalyserImpl *dataAnalyser = new DataAnalyserImpl(robot);

	CPPUNIT_ASSERT(robot->getCallsToGetOdometry() > 0);
	delete dataAnalyser;
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetEngine()
{
	Hardware::RobotMock *robot = new Hardware::RobotMock();
	DataAnalyserImpl *dataAnalyser = new DataAnalyserImpl(robot);

	CPPUNIT_ASSERT(robot->getCallsToGetEngine() > 0);
	delete dataAnalyser;
}
