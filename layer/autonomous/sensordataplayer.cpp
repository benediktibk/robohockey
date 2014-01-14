#include "layer/autonomous/sensordataplayer.h"
#include "layer/hardware/robotmock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/routerimpl.h"
#include "common/watchmock.h"
#include <boost/filesystem.hpp>
#include <assert.h>
#include <fstream>
#include <sstream>

using namespace std;
using namespace boost;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

SensorDataPlayer::SensorDataPlayer(const string &path) :
	m_path(path),
	m_maximumRoundCount(0),
	m_roundCount(0),
	m_watch(new WatchMock()),
	m_hardwareRobot(new Hardware::RobotMock()),
	m_dataAnalyser(new DataAnalysis::DataAnalyserImpl(m_hardwareRobot)),
	m_robot(new Autonomous::RobotImpl(m_dataAnalyser, new RouterImpl(0.38), m_watch)),
	m_field(new FieldImpl(
				m_dataAnalyser->getOdometry(), m_dataAnalyser->getLidar(),
				m_dataAnalyser->getCamera(), *m_robot))
{
	string roundCountFileName = m_path + "/roundcount.txt";
	assert(filesystem::exists(roundCountFileName));
	fstream roundCountFile(roundCountFileName.c_str(), ios::in);
	roundCountFile >> m_maximumRoundCount;
	loadNextRound(0);
}

SensorDataPlayer::~SensorDataPlayer()
{
	delete m_field;
	m_field = 0;
	delete m_robot;
	m_robot = 0;
	m_dataAnalyser = 0;
	m_hardwareRobot = 0;
	m_watch = 0;
}

void SensorDataPlayer::loadNextRound()
{
	++m_roundCount;
	loadNextRound(m_roundCount);
}

unsigned int SensorDataPlayer::getMaximumRoundCount() const
{
	return m_maximumRoundCount;
}

void SensorDataPlayer::loadNextRound(unsigned int roundCount)
{
	Hardware::CameraMock &camera = m_hardwareRobot->getCameraMock();
	Hardware::LidarMock &lidar = m_hardwareRobot->getLidarMock();
	Hardware::OdometryMock &odometry = m_hardwareRobot->getOdometryMock();
	Hardware::EngineMock &engine = m_hardwareRobot->getEngineMock();
	Hardware::SonarMock &sonar = m_hardwareRobot->getSonarMock();

	camera.invalidatePicture();
	stringstream cameraFileName;
	stringstream lidarFileName;
	stringstream sonarFileName;
	stringstream odometryFileName;
	stringstream engineFileName;
	cameraFileName << m_path << "/camera_" << roundCount << ".png";
	lidarFileName << m_path << "/lidar_" << roundCount << ".txt";
	sonarFileName << m_path << "/sonar_" << roundCount << ".txt";
	odometryFileName << m_path << "/odometry_" << roundCount << ".txt";
	engineFileName << m_path << "/engine_" << roundCount << ".txt";

	if (filesystem::exists(cameraFileName.str()))
		camera.readDataFromFile(cameraFileName.str());
	lidar.readDataFromFile(lidarFileName.str());
	odometry.readDataFromFile(odometryFileName.str());
	engine.readDataFromFile(engineFileName.str());
	sonar.readDataFromFile(sonarFileName.str());
}
