#include "layer/view/robotdrivertest.h"
#include "layer/view/robotdriver.h"
#include "layer/view/model.h"
#include "layer/autonomous/robotmock.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::View;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void RobotDriverTest::update_targetReached_targetInModelReached()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	robot.setReachedTarget(true);

	driver.update();

	CPPUNIT_ASSERT(model.reachedTarget());
}

void RobotDriverTest::update_stuckAtObstacle_stuckAtObstacleInModel()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	robot.setStuckAtObstacle(true);

	driver.update();

	CPPUNIT_ASSERT(model.stuckAtObstacle());
}

void RobotDriverTest::update_twoFieldObjects_twoFieldObjectsInModel()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(), FieldObjectColorBlue));
	objects.push_back(FieldObject(Circle(), FieldObjectColorGreen));
	robot.setFieldObjects(objects);

	driver.update();

	const vector<FieldObject> &objectsInModel = model.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInModel.size());
}

void RobotDriverTest::update_stuckAtObstacle_targetPositionsIsEmpty()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	robot.setStuckAtObstacle(true);
	vector<Point> targets;
	targets.push_back(Point());
	model.setData(targets, false, false, false, false, false);

	driver.update();

	const vector<Point> &targetsInModel = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)0, targetsInModel.size());
}

void RobotDriverTest::update_newTargetPositionsAndTargetReached_targetOfRobotIsFirstPosition()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	vector<Point> targets;
	targets.push_back(Point(3, 4));
	targets.push_back(Point(5, 1));
	model.setData(targets, false, false, false, false, false);
	robot.setReachedTarget(true);

	driver.update();

	const Point &currentTarget = robot.getLastTarget();
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(currentTarget, Point(3, 4)));
}

void RobotDriverTest::update_newTargetPositionsAndTargetReached_firstTargetPositionIsMissingInModel()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	vector<Point> targets;
	targets.push_back(Point(3, 4));
	targets.push_back(Point(5, 1));
	model.setData(targets, false, false, false, false, false);
	robot.setReachedTarget(true);

	driver.update();

	vector<Point> currentTargets = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)1, currentTargets.size());
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(currentTargets.front(), Point(5, 1)));
}

void RobotDriverTest::update_newTargetPositionsAndTargetNotReached_targetOfRobotIsUnchanged()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);
	vector<Point> targets;
	targets.push_back(Point(3, 4));
	targets.push_back(Point(5, 1));
	model.setData(targets, false, false, false, false, false);
	robot.setReachedTarget(false);
	robot.goTo(Point(4, 5));

	driver.update();

	vector<Point> currentTargets = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, currentTargets.size());
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(robot.getLastTarget(), Point(4, 5)));
}

void RobotDriverTest::update_empty_robotGotAtLeastOneCallToUpdateSensorData()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);

	driver.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateSensorData() > 0);
}

void RobotDriverTest::update_empty_robotGotAtLeastOneCallToUpdateActuators()
{
	RobotMock robot;
	Model model;
	RobotDriver driver(robot, model);

	driver.update();

	CPPUNIT_ASSERT(robot.getCallsToUpdateActuators() > 0);
}

void RobotDriverTest::update_stuckAtObstacle_noTargetsAnymore()
{
	RobotMock robot;
	robot.setStuckAtObstacle(true);
	Model model;
	RobotDriver driver(robot, model);
	vector<Point> targets;
	targets.push_back(Point(3, 4));
	targets.push_back(Point(5, 1));
	model.setData(targets, false, false, false, false, false);

	driver.update();

	targets = model.getAllTargetPoints();
	CPPUNIT_ASSERT_EQUAL((size_t)0, targets.size());
}
