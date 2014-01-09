#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/robotmock.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void FieldTest::update_noLidarObjects_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarInView_oneObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	lidar.setCanBeSeen(false);
	lidar.setCanBeSeenPartly(false);
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarAndNoObjectFromCamera_noColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCamera_correctColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	camera.setAllObjects(DataAnalysis::CameraObjects());
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_oneObjectOutAndOneObjectInsideOfCalibratedField_correctObjectAddedToField()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((size_t) 4, field.getAllFieldObjects().size());

	CPPUNIT_ASSERT(field.calibratePosition());

	const Point &currentPosition = odometry.getCurrentPosition().getPosition();
	DataAnalysis::LidarObjects lidarObjectsAfterCalibration(currentPosition);
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(1,1), 0.06));
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(-2, 2.6), 0.06));
	lidar.setAllObjects(lidarObjectsAfterCalibration);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t) 3, fieldObjects.size());
	unsigned int found = 0;
	Compare compare(0.01);

	for (vector<FieldObject>::const_iterator i = fieldObjects.begin(); i != fieldObjects.end(); ++i)
	{
		const FieldObject &object = *i;
		const Circle &circle = object.getCircle();
		const Point &position = circle.getCenter();

		if (compare.isFuzzyEqual(Point(1, 1), position))
			++found;
	}
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, found);
}

void FieldTest::update_threeObjectsAndTwoObjectsInGoal_twoAchievedGoals()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, field.getNumberOfAchievedGoals());
}

void FieldTest::update_threeObjectsAndThreeObjectsInGoal_threeAchievedGoals()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfAchievedGoals());
}

void FieldTest::update_fourObjectsAndFourObjectsInGoal_fourAchievedGoals()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.35, 1.6), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.35, 1.6)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, field.getNumberOfAchievedGoals());
}

void FieldTest::update_fourObjectsAndThreeObjectsInGoal_threeAchievedGoals()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.6), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(2, 1.6)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfAchievedGoals());
}

void FieldTest::update_oneObjectAndZeroObjectsInGoal_ZeroAchievedGoals()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.1, 4.3), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0.1, 4.3)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfAchievedGoals());
}

void FieldTest::update_threeObjectsAndTwoObjectsHidden_twoHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.35, 0.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 2.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.35, 0.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 2.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0, 1.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, field.getNumberOfHiddenPucks());
}

void FieldTest::update_threeObjectsAndThreeObjectsHidden_threeHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.34, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 2), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.34, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 2)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfHiddenPucks());
}

void FieldTest::update_threeObjectsAndZeroObjectsHidden_zeroHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 2), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3, 2)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndTwoObjectsHidden_twoHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, field.getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndFourObjectsHidden_fourHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, field.getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndThreeObjectsHidden_threeHiddenPucks()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 1)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfHiddenPucks());
}

void FieldTest::update_threePucksWithTeamColor_30ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)30, testlist.size());
}

void FieldTest::update_fourPucksWithTeamColorInRectangle1_40ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7,3), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 3)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)40, testlist.size());
}

void FieldTest::update_twoPucksWithTeamColorInRectangle2_20ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 2.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 2.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)20, testlist.size());
}

void FieldTest::update_onePuckWithTeamColorInRectangle3_10ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3.02), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3.02)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)10, testlist.size());
}

void FieldTest::update_zeroPucksWithTeamColor_0ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)0, testlist.size());
}

void FieldTest::update_fivePucksWithTeamColorInRectangle4_50ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 0.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 0.6), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.8, 0.3), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 0.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 0.6)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.8, 0.3)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)50, testlist.size());
}

void FieldTest::update_sixPucksWithTeamColorInRectangle5_60ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 2.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 2.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 2.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 2.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)60, testlist.size());
}

void FieldTest::update_sevenPucksWithTeamColorInRectangle6_70ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 0.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 0.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 0.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 0.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 0.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 0.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 0.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 0.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 0.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 0.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 1.8)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)70, testlist.size());
}

void FieldTest::update_eightPucksWithTeamColorInRectangle7_80ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.6, 2.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.7, 2.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 2.3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 2.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.5), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.6, 2.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.7, 2.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 2.3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.9, 2.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.5)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)80, testlist.size());
}

void FieldTest::update_ninePucksWithTeamColorInRectangle8_90ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.7, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 1.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 1.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.6), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 1.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 1.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.7, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 1.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.9, 1.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 1.6)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)90, testlist.size());
}

void FieldTest::update_tenPucksWithTeamColorInRectangle9_100ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 0.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.7, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 0.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 0.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 0.6), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 0.6), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 0.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.7, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.9, 0.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 0.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.61, 0.6)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.9, 0.6)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)100, testlist.size());
}

void FieldTest::getTargetsForFinalPosition_callFunction_17ElementsInList()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	list<RobotPosition> testlist;
	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 0), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	testlist = field.getTargetsForFinalPosition();
	CPPUNIT_ASSERT_EQUAL((size_t)17, testlist.size());
}

void FieldTest::update_objectsInFieldRobotOn00_correctlyUpdated()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	hardwareLidarMock.setValueForAngle(0, 5);
	hardwareLidarMock.setValueForAngle(360, 5);
	hardwareLidarMock.setValueForAngle(282, 1.88);
	hardwareLidarMock.setValueForAngle(283, 1.88);
	hardwareLidarMock.setValueForAngle(284, 1.88);
	hardwareLidarMock.setValueForAngle(285, 1.88);
	hardwareLidarMock.setValueForAngle(286, 1.88);

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)0, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

}

void FieldTest::update_objectsInFieldRobotOn1And2_correctlyUpdated()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	odometry.setCurrentPosition(RobotPosition(Point(1,2), Angle()));

	hardwareLidarMock.setValueForAngle(0, 5);
	hardwareLidarMock.setValueForAngle(360, 5);

	hardwareLidarMock.setValueForAngle(282, 1.88);
	hardwareLidarMock.setValueForAngle(283, 1.88);
	hardwareLidarMock.setValueForAngle(284, 1.88);
	hardwareLidarMock.setValueForAngle(285, 1.88);
	hardwareLidarMock.setValueForAngle(286, 1.88);

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)0, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());
}

void FieldTest::update_movingAndLidarDataChanges_fieldObjectCountDoesntChange()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_1_previous.txt");
	lidar.updateSensorData();
	field.update();
	field.update();
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	odometry.setCurrentPosition(RobotPosition(Point(0.03, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_1_current.txt");
	lidar.updateSensorData();
	field.update();

	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();
	CPPUNIT_ASSERT(oldObjectCount > 0);
	CPPUNIT_ASSERT_EQUAL(oldObjectCount, newObjectCount);
}

void FieldTest::update_movingAndLidatDataChangesSecondVersion_fieldObjectCountDoesntChange()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_2_previous.txt");
	lidar.updateSensorData();
	field.update();
	field.update();
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	odometry.setCurrentPosition(RobotPosition(Point(0.0481614, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_2_current.txt");
	lidar.updateSensorData();
	field.update();
	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();

	CPPUNIT_ASSERT(oldObjectCount > 0);
	CPPUNIT_ASSERT_EQUAL(oldObjectCount, newObjectCount);
}

void FieldTest::update_movingAndLidarDataChangesThirdVersion_fieldObjectCountDoesntChange()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_3_previous.txt");
	lidar.updateSensorData();
	field.update();
	field.update();
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	odometry.setCurrentPosition(RobotPosition(Point(0.0474765, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_moving_3_current.txt");
	lidar.updateSensorData();
	field.update();
	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();

	CPPUNIT_ASSERT_EQUAL((size_t)8, oldObjectCount);
	CPPUNIT_ASSERT_EQUAL((size_t)8, newObjectCount);
}

void FieldTest::update_enemyRobotInFront_oneFieldObject()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_40.txt");

	lidar.updateSensorData();
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_enemyRobotInFront_oneHardObstacle()
{
	DataAnalysis::OdometryMock odometry;
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readSensorDataFromFile("resources/testfiles/lidar_40.txt");

	lidar.updateSensorData();
	field.update();
	field.update();

	vector<Circle> hardObstacles = field.getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)1, hardObstacles.size());
}

void FieldTest::update_lidarReturnsObjectWhichCantBeSeenActually_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(1, 1), 1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(false);
	lidar.setCanBeSeenPartly(false);
	lidar.setAllObjects(objects);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noFieldObjectsAndObstacles()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<Circle> softObstacles = field.getAllSoftObstacles();
	vector<Circle> hardObstacles = field.getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
	CPPUNIT_ASSERT_EQUAL((size_t)0, softObstacles.size());
	CPPUNIT_ASSERT_EQUAL((size_t)0, hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenThreeTimes_oneFieldObjectAndObstacle()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<Circle> softObstacles = field.getAllSoftObstacles();
	vector<Circle> hardObstacles = field.getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	CPPUNIT_ASSERT_EQUAL((size_t)1, softObstacles.size() + hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noObstacles()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();

	vector<Circle> softObstacles = field.getAllSoftObstacles();
	vector<Circle> hardObstacles = field.getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)0, softObstacles.size() + hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenTwice_oneFieldObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_lidarObjectNotSeenOnce_oneFieldObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();
	field.update();
	objects.clear();
	lidar.setAllObjects(objects);
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_lidarObjectNotSeenFiveTimes_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objects(Point(0, 0));
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objects);
	field.update();
	field.update();
	objects.clear();
	lidar.setAllObjects(objects);
	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_collectedPuckAndMovedForward_oneFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	DataAnalysis::LidarObjects objectsPrevious(Point(0, 0));
	objectsPrevious.addObject(DataAnalysis::LidarObject(Point(0.2, 0), 0.04));
	DataAnalysis::LidarObjects objectsAfter(Point(0.1, 0));
	objectsAfter.addObject(DataAnalysis::LidarObject(Point(0.3, 0), 0.04));
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	lidar.setAllObjects(objectsPrevious);
	field.update();
	field.update();
	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	lidar.setAllObjects(objectsAfter);
	field.update();
	field.update();

	fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::calibratePosition_noValidPattern_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT(!field.calibratePosition());
}

void FieldTest::calibratePosition_validPattern_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	CPPUNIT_ASSERT(field.calibratePosition());
}

void FieldTest::calibratePosition_noValidPattern_noTransformation()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);

	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
}

void FieldTest::calibratePosition_validPattern_transformed()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT(!compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
}

void FieldTest::calibratePosition_validPattern_correctNumberOfFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);

	CPPUNIT_ASSERT_EQUAL(lidarObjectsVector.size(), fieldObjects.size());
}

void FieldTest::calibratePosition_validPattern_correctTransformation()
{
	Compare compare(0.05);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();
	field.update();

	bool result = true;
	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	result = result && compare.isFuzzyEqual(fieldObjects.at(0).getCircle().getCenter(), Point(1.666, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(1).getCircle().getCenter(), Point(2.5, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(2).getCircle().getCenter(), Point(3.333, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(3).getCircle().getCenter(), Point(4.582, 0));

	CPPUNIT_ASSERT(result);
}

void FieldTest::calibratePosition_realWorldExample_positionIsCorrect()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot);
	Hardware::OdometryMock &odometry = hardwareRobot->getOdometryMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_35.txt");

	dataAnalyser.updateSensorData();
	field.update();
	field.update();
	field.calibratePosition();
	field.update();

	Compare compare(0.5);
	RobotPosition position = odometry.getCurrentPosition();
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2.5, 1.5), position.getPosition()));
}

void FieldTest::calibratePosition_validPattern_objectsOutsideFieldAreDeleted()
{
	Compare compare(0.05);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5.7, 1.3), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t) 5, fieldObjects.size());

	field.calibratePosition();
	lidar.setCanBeSeen(false);
	lidar.setCanBeSeenPartly(false);
	lidarObjects.clear();
	lidar.setAllObjects(lidarObjects);
	field.update();
	fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t) 4, fieldObjects.size());
}

void FieldTest::getObjectsWithColorOrderedByDistance_oneObjectWithCorrectColorAndOneWithNoColor_resultSizeIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	camera.setAllObjects(cameraObjects);
	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, Point(0, 0));

	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInAscendingOrder_orderIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	camera.setAllObjects(cameraObjects);
	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, ownPosition);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInDescendingOrder_orderIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	camera.setAllObjects(cameraObjects);
	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, ownPosition);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::isPointInsideField_notCalibrated_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();

	CPPUNIT_ASSERT(field.isPointInsideField(Point(-1, -3)));
}

void FieldTest::isPointInsideField_pointIsInside_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(field.isPointInsideField(Point(2,1.5)));
}

void FieldTest::isPointInsideField_pointIsOutside_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(!field.isPointInsideField(Point(0.8,3.2)));
}

void FieldTest::isPointInsideField_pointIsUnderField_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(!field.isPointInsideField(Point(-1,-3)));
}

void FieldTest::getTargetsForGoalDetection_correctPosition()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT_EQUAL(RobotPosition(Point(1.17333333333, 1.5), Angle::getHalfRotation()), field.getTargetsForGoalDetection().front());
}

void FieldTest::getAllSoftObstacles_oneBluePuck_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneGreenObstacle_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneBigObstacle_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_onePuckDisappeared_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	lidarObjects.clear();
	cameraObjects.clear();
	lidar.setAllObjects(lidarObjects);
	camera.setAllObjects(cameraObjects);
	field.update();
	field.update();
	field.update();
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultDiameterIs0p12()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	Circle obstacle = field.getAllSoftObstacles().front();

	CPPUNIT_ASSERT_EQUAL(0.12, obstacle.getDiameter());
}

void FieldTest::getAllHardObstacles_oneGreenObject_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacle_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacleDisappeared_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	lidarObjects.clear();
	lidar.setAllObjects(lidarObjects);
	field.update();
	field.update();
	field.update();
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_fairlyBigObject_diameterIs08()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.14));
	lidar.setAllObjects(lidarObjects);

	lidar.setCanBeSeen(true);
	lidar.setCanBeSeenPartly(true);
	field.update();
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	const Circle &object = obstacles.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8, object.getDiameter(), 0.001);
	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 0), object.getCenter()));
}

void FieldTest::getEnemyTeamColor_OwnTeamColorYellow_blue()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.setTrueTeamColor(FieldColorYellow);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, field.getEnemyTeamColor());
}

void FieldTest::getEnemyTeamColor_OwnTeamColorBlue_yellow()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.setTrueTeamColor(FieldColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, field.getEnemyTeamColor());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsBigger4()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 4 < field.getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForFinalPosition_always_numberOfPositionsBigger1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 1 < field.getTargetsForFinalPosition().size());
}

void FieldTest::getTargetsForSearchingPucks_always_numberOfPositionsBigger5()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 5 < field.getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsForSearchingPucks_twoObjectsWithUnknownColor_numberOfPositions18()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 0.4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.5), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(3, 0.4)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(2, 1.5)));
	camera.setAllObjects(cameraObjects);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((size_t)18, field.getTargetsForSearchingPucks().size());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.82);
	camera.setProbabilityForBlueGoal(0.27);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, field.getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.13);
	camera.setProbabilityForBlueGoal(0.77);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, field.getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowAndBlueEqual_teamNotUnknown()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.47);
	camera.setProbabilityForBlueGoal(0.47);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, field.getOwnTeamColor());
}

void FieldTest::getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin()
{
	//! @todo Test
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_detect1.txt");

	dataAnalyser.updateSensorData();

	field.update();
	unsigned int numberOfBorderStones;
	RobotPosition resultOrigin = field.getNewOriginFromFieldDetection(numberOfBorderStones);
	cout << resultOrigin << endl;

//	Compare compare(0.5);
//	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(0, 0), Angle()), resultOrigin));
	CPPUNIT_ASSERT(true);
}

void FieldTest::getNewOriginFromFieldDetection_realWorldExample2_correctNewOrigin()
{
	//! @todo Test
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_detect2.txt");

	dataAnalyser.updateSensorData();

	field.update();
	unsigned int numberOfBorderStones;
	RobotPosition resultOrigin = field.getNewOriginFromFieldDetection(numberOfBorderStones);
	cout << resultOrigin << endl;

//	Compare compare(0.5);
//	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(0, 0), Angle()), resultOrigin));
	CPPUNIT_ASSERT(true);
}

void FieldTest::getNewOriginFromFieldDetection_realWorldExample3_correctNewOrigin()
{
	//! @todo Test
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_detect3.txt");

	dataAnalyser.updateSensorData();

	field.update();
	unsigned int numberOfBorderStones;
	RobotPosition resultOrigin = field.getNewOriginFromFieldDetection(numberOfBorderStones);
	cout << resultOrigin << endl;

//	Compare compare(0.5);
//	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(0, 0), Angle()), resultOrigin));
	CPPUNIT_ASSERT(true);
}

void FieldTest::getNumberOfObjectsWithColor_noColoredObject_0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfObjectsWithColor(FieldColorUnknown));
}

void FieldTest::getNumberOfObjectsWithColor_3YellowAnd2GreenAnd1UnknownObject_correctValues()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(2, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(3, 1.8)));
	camera.setAllObjects(cameraObjects);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, field.getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, field.getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorUnknown));
}

void FieldTest::getNumberOfObjectsWithColor_2BlueObjects_2()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.8), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(2, 1.8)));
	camera.setAllObjects(cameraObjects);

	field.update();
	field.update();
	field.update();
	field.update();
	field.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, field.getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, field.getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, field.getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, field.getNumberOfObjectsWithColor(FieldColorUnknown));
}
