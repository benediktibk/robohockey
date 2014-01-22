#include "layer/autonomous/fieldlivedatatest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/robotmock.h"
#include "layer/autonomous/sensordataplayer.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include "common/loggermock.h"
#include "common/watchmock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void FieldLiveDataTest::setUp()
{
	m_camera = new DataAnalysis::CameraMock();
	m_lidar = new DataAnalysis::LidarMock();
	m_odometry = new DataAnalysis::OdometryMock();
	m_robot = new RobotMock();
	m_logger = new LoggerMock();
	m_field = new FieldImpl(*m_odometry, *m_lidar, *m_camera, *m_robot, *m_logger);
	m_watchMock = new WatchMock();
}

void FieldLiveDataTest::tearDown()
{
	delete m_field;
	m_field = 0;
	delete m_camera;
	m_camera = 0;
	delete m_lidar;
	m_lidar = 0;
	delete m_odometry;
	m_odometry = 0;
	delete m_robot;
	m_robot = 0;
	delete m_logger;
	m_logger = 0;
	delete m_watchMock;
	m_watchMock = 0;
}

void FieldLiveDataTest::update_changingData_noColoredObjectsAreLost()
{
	SensorDataPlayer sensorDataPlayer("resources/testfiles/loosing_puck_1");

	for (unsigned int round = 0; round < sensorDataPlayer.getMaximumRoundCount(); ++round)
	{
		sensorDataPlayer.loadNextRound();
		if (sensorDataPlayer.countOfColoredObjectsDecreased())
			CPPUNIT_ASSERT(false);
	}

	CPPUNIT_ASSERT(sensorDataPlayer.getBlueObjectCount() > 0);
}

void FieldLiveDataTest::update_changingData2_noColoredObjectsAreLost()
{
	SensorDataPlayer sensorDataPlayer("resources/testfiles/loosing_puck_2");

	for (unsigned int round = 0; round < sensorDataPlayer.getMaximumRoundCount(); ++round)
	{
		sensorDataPlayer.loadNextRound();
		if (sensorDataPlayer.countOfColoredObjectsDecreased())
			CPPUNIT_ASSERT(false);
	}

	CPPUNIT_ASSERT(sensorDataPlayer.getBlueObjectCount() > 0);
}

void FieldLiveDataTest::calibratePosition_goodRealWorldExample_positionIsCorrect()
{
	SensorDataPlayer sensorDataPlayer("resources/testfiles/field_detection_perfect");

	for (unsigned int round = 0; round < sensorDataPlayer.getMaximumRoundCount(); ++round)
		sensorDataPlayer.loadNextRound();

	Field &field = sensorDataPlayer.getField();
	CPPUNIT_ASSERT(field.calibratePosition());
	Point position = sensorDataPlayer.getCurrentPosition();
	Compare compare(0.2);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.6, 1.5), position));
}

void FieldLiveDataTest::calibratePosition_worstCaseRealWorldExample_positionIsCorrect()
{
	SensorDataPlayer sensorDataPlayer("resources/testfiles/field_detection_worst_case");

	for (unsigned int round = 0; round < sensorDataPlayer.getMaximumRoundCount(); ++round)
		sensorDataPlayer.loadNextRound();

	Field &field = sensorDataPlayer.getField();
	CPPUNIT_ASSERT(field.calibratePosition());
	Point position = sensorDataPlayer.getCurrentPosition();
	Compare compare(0.2);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.6, 1.5), position));
}

void FieldLiveDataTest::calibratePosition_anotherRealWorldExample_positionIsCorrect()
{
	SensorDataPlayer sensorDataPlayer("resources/testfiles/field_detection_1");

	for (unsigned int round = 0; round < sensorDataPlayer.getMaximumRoundCount(); ++round)
		sensorDataPlayer.loadNextRound();

	Field &field = sensorDataPlayer.getField();
	CPPUNIT_ASSERT(field.calibratePosition());
	Point position = sensorDataPlayer.getCurrentPosition();
	Compare compare(0.3);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1.1, 0.4), position));
}

void FieldLiveDataTest::updateFieldForObjectsToAppear(FieldImpl &field)
{
	field.update();
	field.update();
}

void FieldLiveDataTest::updateFieldForObjectsToDisappear(FieldImpl &field)
{
	field.update();
	field.update();
	field.update();
	field.update();
	field.update();
}

void FieldLiveDataTest::updateFieldForObjectsToAppear()
{
	updateFieldForObjectsToAppear(*m_field);
}

void FieldLiveDataTest::updateFieldForObjectsToDisappear()
{
	updateFieldForObjectsToDisappear(*m_field);
}
