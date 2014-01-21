#include "layer/dataanalysis/dataanalysertest.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/watchmock.h"
#include "common/loggermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void DataAnalyserTest::setUp()
{
	m_watch = new WatchMock();
	m_logger = new LoggerMock();
	m_hardwareRobot = new Hardware::RobotMock();
	m_dataAnalyser = new DataAnalyserImpl(m_hardwareRobot, *m_watch, *m_logger);
}

void DataAnalyserTest::tearDown()
{
	delete m_dataAnalyser;
	m_dataAnalyser = 0;
	delete m_watch;
	m_watch = 0;
	delete m_logger;
	m_logger = 0;
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetSonar()
{
	CPPUNIT_ASSERT(m_hardwareRobot->getCallsToGetSonar() > 0);
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetLidar()
{
	CPPUNIT_ASSERT(m_hardwareRobot->getCallsToGetLidar() > 0);
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetCamera()
{
	CPPUNIT_ASSERT(m_hardwareRobot->getCallsToGetCamera() > 0);
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetOdometry()
{
	CPPUNIT_ASSERT(m_hardwareRobot->getCallsToGetOdometry() > 0);
}

void DataAnalyserTest::constructor_mockRobot_atLeastOneCallToGetEngine()
{
	CPPUNIT_ASSERT(m_hardwareRobot->getCallsToGetEngine() > 0);
}
