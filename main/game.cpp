#include "main/game.h"
#include "main/inputargumentparser.h"
#include "common/watchimpl.h"
#include "common/segfaultstacktraceprinter.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotimpl.h"
#include "layer/hardware/sensordatarecorder.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/strategy/common/refereeimpl.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <assert.h>

using namespace std;
using namespace RoboHockey;
using namespace RoboHockey::Common;
using namespace RoboHockey::Main;
using namespace RoboHockey::Layer;

Game::Game(int argc, char **argv) :
	m_robot(0),
	m_field(0),
	m_referee(0),
	m_watch(new Common::WatchImpl()),
	m_timer(new QTimer()),
	m_loopTimeMaximum(0.2),
	m_loopTimeWeight(0.1),
	m_loopTimeAverage(0),
	m_blueObjectCount(0),
	m_yellowObjectCount(0),
	m_greenObjectCount(0),
	m_stackTracePrinter(new SegFaultStackTracePrinter()),
	m_consoleMessagesEnabled(false),
	m_valid(true),
	m_sensorDataRecorder(0)
{
	InputArgumentParser parser(InputArgumentParser::convertArguments(argc, argv));

	if (!parser.isValid())
	{
		cout << "invalid arguments" << endl;
		cout << parser.usage();
		m_valid = false;
		exit(1);
	}

	string playerServer = parser.playerServer();
	string angelinaServer = parser.angelinaServer();
	m_enableGui = parser.enableGui();

	cout << "##### ---------------------------\n##### GAME START" << endl;
	cout << "##### player ip     : " << playerServer << endl;
	cout << "##### angelina ip   : " << angelinaServer << endl;

	if (m_enableGui)
		cout << "##### GUI Enabled   : " << "TRUE" << endl;
	else
		cout << "##### GUI Enabled   : " << "FALSE" << endl;

	if (parser.enableRecorder())
		cout << "##### recording to  : " << parser.recordingPath() << endl;
	cout << "##### ---------------------------" << endl;

	Hardware::Robot *hardwareRobot = new Hardware::RobotImpl(playerServer);
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Autonomous::Router *router = new Autonomous::RouterImpl(0.38);
	m_robot = new Autonomous::RobotImpl(dataAnalyser, router, new Common::WatchImpl());
	m_field = new Autonomous::FieldImpl(
				dataAnalyser->getOdometry(), dataAnalyser->getLidar(),
				dataAnalyser->getCamera(), *m_robot);
	m_referee = new Strategy::Common::RefereeImpl(angelinaServer);

	if (parser.enableRecorder())
		m_sensorDataRecorder = new Hardware::SensorDataRecorder(*hardwareRobot, parser.recordingPath());

	connect(m_timer, SIGNAL(timeout()), this, SLOT(execute()));

	m_watch->getTimeAndRestart();
	m_timer->start(0);
	m_referee->reportReady();
}

Game::~Game()
{
	delete m_sensorDataRecorder;
	m_sensorDataRecorder = 0;
	delete m_watch;
	m_watch = 0;
	delete m_field;
	m_field = 0;
	delete m_robot;
	m_robot = 0;
	delete m_referee;
	m_referee = 0;
	delete m_timer;
	m_timer = 0;
	delete m_stackTracePrinter;
	m_stackTracePrinter = 0;
}

bool Game::guiEnabled()
{
	assert(m_valid);
	return m_enableGui;
}

void Game::setLogMessagesEnabled(bool enable)
{
	assert(m_valid);
	m_consoleMessagesEnabled = enable;
}

bool Game::logMessagesEnabled()
{
	assert(m_valid);
	return m_consoleMessagesEnabled;
}

void Game::logToConsole(const string &message)
{
	assert(m_valid);
	if (logMessagesEnabled())
		cout << message << endl;
}

void Game::execute()
{
	assert(m_valid);
	WatchImpl watch;

	/*!
	 * Unfortunately disabling the engine is very slow, this seems
	 * to be a blocking call. If we then decide to stop and disable
	 * the engine we would get in this iteration a very high loop time.
	 * After this step the robot would say he is not moving anymore,
	 * but still the loop time is very high. Therefore we check if
	 * the robot is moving previously to avoid this problem.
	 */
	bool isMovingPreviously = m_robot->isMoving();
	m_robot->updateSensorData();

	if (m_sensorDataRecorder != 0)
		m_sensorDataRecorder->recordCurrentValues();

	double timeForSensorUpdate = watch.getTimeAndRestart();

	m_field->update();
	double blueObjectCountNew = m_field->getNumberOfObjectsWithColor(FieldColorBlue);
	double yellowObjectCountNew = m_field->getNumberOfObjectsWithColor(FieldColorYellow);
	double greenObjectCountNew = m_field->getNumberOfObjectsWithColor(FieldColorGreen);
	double timeForFieldUpdate = watch.getTimeAndRestart();

	executeRobotControl();
	double timeForLogic = watch.getTimeAndRestart();

	m_robot->updateActuators(*m_field);
	m_referee->tellEgoPos(m_robot->getCurrentPosition().getPosition());
	m_referee->sendAlive();
	double timeForActuatorUpdate = watch.getTimeAndRestart();
	bool isMovingAfterwards = m_robot->isMoving();

	double timeDifference = m_watch->getTimeAndRestart();
	double timeForEventProcessing =
			timeDifference -
			(timeForActuatorUpdate + timeForFieldUpdate + timeForLogic + timeForSensorUpdate);

	/*!
	 * Sometimes we get very high peaks for just one loop, caused by the player library.
	 * To avoid this we only look at the moving average of the loop time.
	 */
	m_loopTimeAverage = m_loopTimeAverage*(1 - m_loopTimeWeight) + m_loopTimeWeight*timeDifference;

	/*!
	 * Actually we get data every 100ms, but the Read-function of
	 * the player client sometimes needs up to 160ms.
	 */
	if (m_loopTimeAverage > m_loopTimeMaximum && timeDifference > m_loopTimeMaximum && isMovingPreviously && isMovingAfterwards)
	{
		printTimeInMs("loop time is too high", timeDifference);
		printTimeInMs("time spent on sensor updates", timeForSensorUpdate);
		printTimeInMs("time spent on field update", timeForFieldUpdate);
		printTimeInMs("time spent on logic", timeForLogic);
		printTimeInMs("time spent on actuator updates", timeForActuatorUpdate);
		printTimeInMs("time spent on event processing", timeForEventProcessing);
	}

	if (blueObjectCountNew != m_blueObjectCount)
	{
		stringstream stream;
		stream << blueObjectCountNew << " blue objects are known";
		logToConsole(stream.str());
		m_blueObjectCount = blueObjectCountNew;
	}

	if (yellowObjectCountNew != m_yellowObjectCount)
	{
		stringstream stream;
		stream << yellowObjectCountNew << " yellow objects are known" << endl;
		logToConsole(stream.str());
		m_yellowObjectCount = yellowObjectCountNew;
	}

	if (greenObjectCountNew != m_greenObjectCount)
	{
		stringstream stream;
		stream << greenObjectCountNew << " green objects are known" << endl;
		logToConsole(stream.str());
		m_greenObjectCount = greenObjectCountNew;
	}

	if (keepRunning())
		m_timer->start(0);
	else
		QCoreApplication::quit();
}

Autonomous::Robot &Game::getRobot()
{
	assert(m_valid);
	return *m_robot;
}

Autonomous::Field &Game::getField()
{
	assert(m_valid);
	return *m_field;
}

Strategy::Common::Referee &Game::getReferee()
{
	assert(m_valid);
	return *m_referee;
}

void Game::printTimeInMs(const string &message, double time) const
{
	assert(m_valid);
	cout << setprecision(1) << fixed << message << ": " << time*1000 << " ms" << endl;
}

