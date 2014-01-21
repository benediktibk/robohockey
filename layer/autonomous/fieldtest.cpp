#include "layer/autonomous/fieldtest.h"
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

void FieldTest::setUp()
{
	m_camera = new DataAnalysis::CameraMock();
	m_lidar = new DataAnalysis::LidarMock();
	m_odometry = new DataAnalysis::OdometryMock();
	m_robot = new RobotMock();
	m_logger = new LoggerMock();
	m_field = new FieldImpl(*m_odometry, *m_lidar, *m_camera, *m_robot, *m_logger);
	m_watchMock = new WatchMock();
}

void FieldTest::tearDown()
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

void FieldTest::update_noLidarObjects_noFieldObjects()
{
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarInView_oneObject()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	updateFieldForObjectsToAppear();
	m_lidar->setAllObjects(DataAnalysis::LidarObjects());
	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	updateFieldForObjectsToAppear();
	m_lidar->setAllObjects(DataAnalysis::LidarObjects());
	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	updateFieldForObjectsToAppear();
	m_lidar->setAllObjects(DataAnalysis::LidarObjects());
	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_lidar->setAllObjects(DataAnalysis::LidarObjects());
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_lidar->setCanBeSeen(false);
	m_lidar->setCanBeSeenPartly(false);
	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarAndNoObjectFromCamera_noColor()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCamera_correctColor()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_camera->setAllObjects(DataAnalysis::CameraObjects());
	m_field->update();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_oneObjectOutAndOneObjectInsideOfCalibratedField_correctObjectAddedToField()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t) 4, m_field->getAllFieldObjects().size());

	CPPUNIT_ASSERT(m_field->calibratePosition());
	CPPUNIT_ASSERT(m_field->isCalibrated());

	DataAnalysis::LidarObjects lidarObjectsAfterCalibration;
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(0.666, 0.5), 0.06));
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(-2, 2.6), 0.06));
	m_lidar->setAllObjects(lidarObjectsAfterCalibration);

	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	unsigned int found = 0;
	Compare compare(0.01);

	for (vector<FieldObject>::const_iterator i = fieldObjects.begin(); i != fieldObjects.end(); ++i)
	{
		const FieldObject &object = *i;
		const Circle &circle = object.getCircle();
		const Point &position = circle.getCenter();

		if (compare.isFuzzyEqual(Point(0.666, 0.5), position))
			++found;
	}
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, found);
}

void FieldTest::update_threeObjectsAndTwoObjectsInGoal_twoAchievedGoals()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfAchievedGoals());
}

void FieldTest::update_threeObjectsAndThreeObjectsInGoal_threeAchievedGoals()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfAchievedGoals());
}

void FieldTest::update_fourObjectsAndFourObjectsInGoal_fourAchievedGoals()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.35, 1.6), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.35, 1.6)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, m_field->getNumberOfAchievedGoals());
}

void FieldTest::update_fourObjectsAndThreeObjectsInGoal_threeAchievedGoals()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.6), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.3, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(2, 1.6)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfAchievedGoals());
}

void FieldTest::update_oneObjectAndZeroObjectsInGoal_ZeroAchievedGoals()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.1, 4.3), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0.1, 4.3)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfAchievedGoals());
}

void FieldTest::update_threeObjectsAndTwoObjectsHidden_twoHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.35, 0.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 2.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.35, 0.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 2.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_threeObjectsAndThreeObjectsHidden_threeHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.34, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.34, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 2)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_threeObjectsAndZeroObjectsHidden_zeroHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3, 2)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndTwoObjectsHidden_twoHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndFourObjectsHidden_fourHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorBlue);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)4, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_fourObjectsAndThreeObjectsHidden_threeHiddenPucks()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(3.5, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 1)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfHiddenPucks());
}

void FieldTest::update_threePucksWithTeamColor_30ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.4, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 2)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)30, testlist.size());
}

void FieldTest::update_fourPucksWithTeamColorInRectangle1_40ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7,3), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 3)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)40, testlist.size());
}

void FieldTest::update_twoPucksWithTeamColorInRectangle2_20ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 2.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 2.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)20, testlist.size());
}

void FieldTest::update_onePuckWithTeamColorInRectangle3_10ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3.02), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3.02)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)10, testlist.size());
}

void FieldTest::update_zeroPucksWithTeamColor_0ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)0, testlist.size());
}

void FieldTest::update_fivePucksWithTeamColorInRectangle4_50ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.7, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 0.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4, 0.6), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.8, 0.3), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.7, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 0.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4, 0.6)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.8, 0.3)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)50, testlist.size());
}

void FieldTest::update_sixPucksWithTeamColorInRectangle5_60ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 2.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 2.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 2.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 2.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)60, testlist.size());
}

void FieldTest::update_sevenPucksWithTeamColorInRectangle6_70ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.16, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 0.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.14, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 0.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 0.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 0.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 0.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.16, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 0.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.14, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 0.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 0.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 0.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 0.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.5, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)70, testlist.size());
}

void FieldTest::update_eightPucksWithTeamColorInRectangle7_80ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.6, 2.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.7, 2.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 2.3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 2.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 2.5), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.02)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(5, 3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.6, 2.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.7, 2.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.8, 2.3)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.9, 2.9)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 2.5)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)80, testlist.size());
}

void FieldTest::update_ninePucksWithTeamColorInRectangle8_90ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.02), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.7, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.8, 1.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.9, 1.9), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.61, 1.6), 0.1));
	m_lidar->setAllObjects(lidarObjects);
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
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)90, testlist.size());
}

void FieldTest::update_tenPucksWithTeamColorInRectangle9_100ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
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
	m_lidar->setAllObjects(lidarObjects);
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
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForCollectingOnePuck(FieldColorYellow);
	CPPUNIT_ASSERT_EQUAL((size_t)100, testlist.size());
}

void FieldTest::getTargetsForFinalPosition_callFunction_17ElementsInList()
{
	list<RobotPosition> testlist;
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.59, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.59, 0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	testlist = m_field->getTargetsForFinalPosition();
	CPPUNIT_ASSERT_EQUAL((size_t)17, testlist.size());
}

void FieldTest::update_objectsInFieldRobotOn00_correctlyUpdated()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);

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
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());
}

void FieldTest::update_objectsInFieldRobotOn1And2_correctlyUpdated()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);

	m_odometry->setCurrentPosition(RobotPosition(Point(1, 2), Angle()));

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
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	CPPUNIT_ASSERT_EQUAL((size_t)1, field.getAllFieldObjects().size());
}

void FieldTest::update_movingAndLidarDataChanges_fieldObjectCountDoesntChange()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);

	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_1_previous.txt");
	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	m_odometry->setCurrentPosition(RobotPosition(Point(0.03, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_1_current.txt");
	lidar.updateSensorData();
	field.update();

	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();
	CPPUNIT_ASSERT(oldObjectCount > 0);
	CPPUNIT_ASSERT_EQUAL(oldObjectCount, newObjectCount);
}

void FieldTest::update_movingAndLidatDataChangesSecondVersion_fieldObjectCountDoesntChange()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);

	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_2_previous.txt");
	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	m_odometry->setCurrentPosition(RobotPosition(Point(0.0481614, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_2_current.txt");
	lidar.updateSensorData();
	field.update();
	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();

	CPPUNIT_ASSERT(oldObjectCount > 0);
	CPPUNIT_ASSERT_EQUAL(oldObjectCount, newObjectCount);
}

void FieldTest::update_movingAndLidarDataChangesThirdVersion_fieldObjectCountDoesntChange()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);

	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_3_previous.txt");
	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);
	vector<FieldObject> oldObjects = field.getAllFieldObjects();
	size_t oldObjectCount = oldObjects.size();
	m_odometry->setCurrentPosition(RobotPosition(Point(0.0474765, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_moving_3_current.txt");
	lidar.updateSensorData();
	field.update();
	vector<FieldObject> newObjects = field.getAllFieldObjects();
	size_t newObjectCount = newObjects.size();

	CPPUNIT_ASSERT_EQUAL((size_t)8, oldObjectCount);
	CPPUNIT_ASSERT_EQUAL((size_t)8, newObjectCount);
}

void FieldTest::update_enemyRobotInFront_oneFieldObject()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_40.txt");

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_enemyRobotInFront_oneHardObstacle()
{
	Hardware::LidarMock hardwareLidarMock(6);
	DataAnalysis::LidarImpl lidar(hardwareLidarMock);
	FieldImpl field(*m_odometry, lidar, *m_camera, *m_robot, *m_logger);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	hardwareLidarMock.readDataFromFile("resources/testfiles/lidar_40.txt");

	lidar.updateSensorData();
	updateFieldForObjectsToAppear(field);

	vector<Circle> hardObstacles = field.getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)1, hardObstacles.size());
}

void FieldTest::update_lidarReturnsObjectWhichCantBeSeenActually_noFieldObjects()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(1, 1), 1));

	m_lidar->setCanBeSeen(false);
	m_lidar->setCanBeSeenPartly(false);
	m_lidar->setAllObjects(objects);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noFieldObjectsAndObstacles()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	m_field->update();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	vector<Circle> softObstacles = m_field->getAllSoftObstacles();
	vector<Circle> hardObstacles = m_field->getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
	CPPUNIT_ASSERT_EQUAL((size_t)0, softObstacles.size());
	CPPUNIT_ASSERT_EQUAL((size_t)0, hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenThreeTimes_oneFieldObjectAndObstacle()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	vector<Circle> softObstacles = m_field->getAllSoftObstacles();
	vector<Circle> hardObstacles = m_field->getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	CPPUNIT_ASSERT_EQUAL((size_t)1, softObstacles.size() + hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noFieldObjects()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	m_field->update();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_lidarObjectSeenOnlyOnce_noObstacles()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	m_field->update();

	vector<Circle> softObstacles = m_field->getAllSoftObstacles();
	vector<Circle> hardObstacles = m_field->getAllHardObstacles();
	CPPUNIT_ASSERT_EQUAL((size_t)0, softObstacles.size() + hardObstacles.size());
}

void FieldTest::update_lidarObjectSeenTwice_oneFieldObject()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_lidarObjectNotSeenOnce_oneFieldObject()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	updateFieldForObjectsToAppear();
	objects.clear();
	m_lidar->setAllObjects(objects);
	m_field->update();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_lidarObjectNotSeenOften_noFieldObjects()
{
	DataAnalysis::LidarObjects objects;
	objects.addObject(DataAnalysis::LidarObject(Point(2, 0), 0.1));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objects);
	updateFieldForObjectsToAppear();
	objects.clear();
	m_lidar->setAllObjects(objects);

	updateFieldForObjectsToDisappear();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_collectedPuckAndMovedForward_oneFieldObject()
{
	DataAnalysis::LidarObjects objectsPrevious;
	objectsPrevious.addObject(DataAnalysis::LidarObject(Point(0.2, 0), 0.04));
	DataAnalysis::LidarObjects objectsAfter;
	objectsAfter.addObject(DataAnalysis::LidarObject(Point(0.3, 0), 0.04));
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objectsPrevious);
	updateFieldForObjectsToAppear();
	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	m_lidar->setAllObjects(objectsAfter);
	updateFieldForObjectsToDisappear();

	fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_rotatingAndObjectALittleBitDistanceMoved_onlyFieldObjectStaysTheSame()
{
	DataAnalysis::LidarObjects objectsPrevious;
	objectsPrevious.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.04));
	DataAnalysis::LidarObjects objectsAfter;
	objectsAfter.addObject(DataAnalysis::LidarObject(Point(1, 0.1), 0.04));
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objectsPrevious);
	m_robot->setIsRotating(false);
	updateFieldForObjectsToAppear();
	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	m_lidar->setAllObjects(objectsAfter);
	m_robot->setIsRotating(true);
	updateFieldForObjectsToDisappear();

	fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	FieldObject &fieldObject = fieldObjects.front();
	Compare compare(0.000001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.04), fieldObject.getCircle()));
}

void FieldTest::update_rotatingAndObjectVeryClose_onlyFieldObjectIsUpdated()
{
	DataAnalysis::LidarObjects objectsPrevious;
	objectsPrevious.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.04));
	DataAnalysis::LidarObjects objectsAfter;
	objectsAfter.addObject(DataAnalysis::LidarObject(Point(1, 0.1), 0.04));
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_lidar->setAllObjects(objectsPrevious);
	m_robot->setIsRotating(false);
	updateFieldForObjectsToAppear();
	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	m_lidar->setAllObjects(objectsAfter);
	m_robot->setIsRotating(false);
	updateFieldForObjectsToDisappear();

	fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
	FieldObject &fieldObject = fieldObjects.front();
	Compare compare(0.000001);
	CPPUNIT_ASSERT(!compare.isFuzzyEqual(Circle(Point(1, 0), 0.04), fieldObject.getCircle()));
}

void FieldTest::calibratePosition_noValidPattern_false()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(!m_field->calibratePosition());
	CPPUNIT_ASSERT(!m_field->isCalibrated());
}

void FieldTest::calibratePosition_validPattern_true()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 5.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->calibratePosition());
	CPPUNIT_ASSERT(m_field->isCalibrated());
}

void FieldTest::calibratePosition_noValidPattern_noTransformation()
{
	Compare compare(0.01);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(m_odometry->getCurrentPosition(), 10);

	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
	CPPUNIT_ASSERT(!m_field->isCalibrated());
}

void FieldTest::calibratePosition_validPattern_transformed()
{
	Compare compare(0.01);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();
	m_field->update();

	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(m_odometry->getCurrentPosition(), 10);
	CPPUNIT_ASSERT(fieldObjects.size() > 0);
	CPPUNIT_ASSERT(!compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
	CPPUNIT_ASSERT(m_field->isCalibrated());
}

void FieldTest::calibratePosition_validPattern_correctNumberOfFieldObjects()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();
	updateFieldForObjectsToDisappear();

	CPPUNIT_ASSERT(m_field->isCalibrated());
}

void FieldTest::calibratePosition_validPattern_correctTransformation()
{
	Compare compare(0.05);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();
	m_field->update();

	CPPUNIT_ASSERT(m_field->isCalibrated());
}

void FieldTest::calibratePosition_realWorldExample_positionIsCorrect()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot, *m_watchMock);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot, *m_logger);
	Hardware::OdometryMock &odometry = hardwareRobot->getOdometryMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readDataFromFile("resources/testfiles/lidar_35.txt");

	dataAnalyser.updateSensorData();
	updateFieldForObjectsToAppear(field);
	field.calibratePosition();
	field.update();

	Compare compare(0.5);
	RobotPosition position = odometry.getCurrentPosition();
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2.5, 1.5), position.getPosition()));
	CPPUNIT_ASSERT(field.isCalibrated());
}

void FieldTest::calibratePosition_validPattern_objectsOutsideFieldAreDeleted()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5.7, 1.3), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<FieldObject> fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t) 5, fieldObjects.size());

	m_field->calibratePosition();
	m_lidar->setCanBeSeen(false);
	m_lidar->setCanBeSeenPartly(false);
	lidarObjects.clear();
	m_lidar->setAllObjects(lidarObjects);
	updateFieldForObjectsToDisappear();

	fieldObjects = m_field->getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t) 4, fieldObjects.size());
	CPPUNIT_ASSERT(m_field->isCalibrated());
}

void FieldTest::getObjectsWithColorOrderedByDistance_oneObjectWithCorrectColorAndOneWithNoColor_resultSizeIsCorrect()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getObjectsWithColorOrderdByDistance(FieldColorYellow);

	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInAscendingOrder_orderIsCorrect()
{
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	m_camera->setAllObjects(cameraObjects);
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_odometry->setCurrentPosition(RobotPosition(ownPosition, 0));
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getObjectsWithColorOrderdByDistance(FieldColorYellow);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInDescendingOrder_orderIsCorrect()
{
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	m_odometry->setCurrentPosition(RobotPosition(ownPosition, 0));
	updateFieldForObjectsToAppear();

	vector<FieldObject> fieldObjects = m_field->getObjectsWithColorOrderdByDistance(FieldColorYellow);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::isPointInsideField_notCalibrated_true()
{
	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPointInsideField(Point(-1, -3)));
}

void FieldTest::isPointInsideField_pointIsInside_true()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();

	CPPUNIT_ASSERT(m_field->isCalibrated());
	CPPUNIT_ASSERT(m_field->isPointInsideField(Point(2,1.5)));
}

void FieldTest::isPointInsideField_pointIsOutside_false()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();

	CPPUNIT_ASSERT(m_field->isCalibrated());
	CPPUNIT_ASSERT(!m_field->isPointInsideField(Point(0.8,3.2)));
}

void FieldTest::isPointInsideField_pointIsUnderField_false()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.417), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.5), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	m_odometry->setCurrentPosition(RobotPosition(Point(0,2), Angle()));

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	m_field->calibratePosition();

	CPPUNIT_ASSERT(m_field->isCalibrated());
	CPPUNIT_ASSERT(!m_field->isPointInsideField(Point(-1,-3)));
}

void FieldTest::getTargetsForGoalDetection_correctPosition()
{
	CPPUNIT_ASSERT_EQUAL(RobotPosition(Point(1.17333333333, 1.5), Angle::getHalfRotation()), m_field->getTargetsForGoalDetection().front());
}

void FieldTest::getAllSoftObstacles_oneBluePuck_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneGreenObstacle_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneBigObstacle_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_onePuckDisappeared_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	lidarObjects.clear();
	cameraObjects.clear();
	m_lidar->setAllObjects(lidarObjects);
	m_camera->setAllObjects(cameraObjects);
	updateFieldForObjectsToDisappear();

	vector<Circle> obstacles = m_field->getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultDiameterIs0p12()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	Circle obstacle = m_field->getAllSoftObstacles().front();

	CPPUNIT_ASSERT_EQUAL(0.12, obstacle.getDiameter());
}

void FieldTest::getAllHardObstacles_oneGreenObject_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacle_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacleDisappeared_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	lidarObjects.clear();
	m_lidar->setAllObjects(lidarObjects);
	updateFieldForObjectsToDisappear();
	vector<Circle> obstacles = m_field->getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_fairlyBigObject_diameterIs08()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.14));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	const Circle &object = obstacles.front();
	CPPUNIT_ASSERT(object.getDiameter() >  0.5);
	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 0), object.getCenter()));
}

void FieldTest::getAllHardAndVisibleObstacles_hardObstacleWhichCantBeSeen_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.3));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeenPartly(false);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardAndVisibleObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardAndVisibleObstacles_visibleSoftObstacle_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.03));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardAndVisibleObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardAndVisibleObstacles_visibleButTooDistantHardObstacle_resultSizeIs0()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(10, 0), 0.3));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardAndVisibleObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardAndVisibleObstacles_hardAndVisibleObstacle_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.3));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	vector<Circle> obstacles = m_field->getAllHardAndVisibleObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardAndVisibleObstacles_possibleCandidateOnceNotSeen_resultSizeIs1()
{
	RobotPosition ownPosition(Point(0, 0), 0);
	m_odometry->setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.3));
	m_lidar->setAllObjects(lidarObjects);

	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();
	lidarObjects.clear();
	m_lidar->setAllObjects(lidarObjects);
	m_lidar->setCanBeSeenPartly(false);
	m_field->update();
	vector<Circle> obstacles = m_field->getAllHardAndVisibleObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getEnemyTeamColor_OwnTeamColorYellow_blue()
{
	m_field->setTrueTeamColor(FieldColorYellow);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, m_field->getEnemyTeamColor());
}

void FieldTest::getEnemyTeamColor_OwnTeamColorBlue_yellow()
{
	m_field->setTrueTeamColor(FieldColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, m_field->getEnemyTeamColor());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsBigger4()
{
	CPPUNIT_ASSERT((size_t) 4 < m_field->getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsBigger5()
{
	m_field->increaseNumberOfEstimatedGoals();

	CPPUNIT_ASSERT((size_t) 5 < m_field->getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsBigger6()
{
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();

	CPPUNIT_ASSERT((size_t) 5 < m_field->getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsIs16()
{
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();

	CPPUNIT_ASSERT_EQUAL((size_t)16, m_field->getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForScoringGoals_forEstimatedGoalsAre0AndEstimatedGoalsAre3_positionsAreEqual()
{
	Compare compare(0.1);
	list<RobotPosition> estimated0, estimated3;
	estimated0 = m_field->getTargetsForScoringGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	estimated3 = m_field->getTargetsForScoringGoals();

	CPPUNIT_ASSERT(compare.isFuzzyEqual(estimated0, estimated3));
}

void FieldTest::getTargetsForScoringGoals_forEstimatedGoalsAre1AndEstimatedGoalsAre4_positionsAreEqual()
{
	Compare compare(0.1);
	list<RobotPosition> estimated1, estimated4;
	m_field->increaseNumberOfEstimatedGoals();
	estimated1 = m_field->getTargetsForScoringGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	estimated4 = m_field->getTargetsForScoringGoals();

	CPPUNIT_ASSERT(compare.isFuzzyEqual(estimated1, estimated4));
}

void FieldTest::getTargetsForScoringGoals_forEstimatedGoalsAre2AndEstimatedGoalsAre5_positionsAreEqual()
{
	Compare compare(0.1);
	list<RobotPosition> estimated2, estimated5;
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	estimated2 = m_field->getTargetsForScoringGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();
	estimated5 = m_field->getTargetsForScoringGoals();

	CPPUNIT_ASSERT(compare.isFuzzyEqual(estimated2, estimated5));
}

void FieldTest::getTargetsForFinalPosition_always_numberOfPositionsBigger1()
{
	CPPUNIT_ASSERT((size_t) 1 < m_field->getTargetsForFinalPosition().size());
}

void FieldTest::getTargetsForSearchingPucks_always_numberOfPositionsBigger5()
{
	CPPUNIT_ASSERT((size_t) 5 < m_field->getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsForSearchingPucks_twoObjectsWithUnknownColor_numberOfPositions33()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 0.4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.5), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(3, 0.4)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(2, 1.5)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)33, m_field->getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsForSearchingPucks_threeObjectsWithUnknownColor_numberOfPositions43()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 0.4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.5, 1.1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(3, 0.4)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.5, 1.1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)43, m_field->getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsForSearchingPucks_threeObjectsWithUnknownColorNotInField_numberOfPositions10()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, -0.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5.3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(6, 1.5), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0, -0.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(5.3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(6, 1.5)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)13, m_field->getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsForSearchungPucks_fourObjectsWithUnknownColorAndOneObjectWithKnownColorAndTwoPucksWithUnknownColorNotInField_numberOfPositions33()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0, -0.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5.3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2.5, 2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0, -0.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(5.3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(2, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2.5, 2)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)33, m_field->getTargetsForSearchingPucks().size());
}

void FieldTest::getTargetsInEnemyThird_always_numberOfPositionsBiggerThan4()
{
	CPPUNIT_ASSERT((size_t) 4 < m_field->getTargetsInEnemyThird().size());
}

void FieldTest::getTargetsForWaitingPhase_always_numberOfPositionsBiggerThan2()
{
	CPPUNIT_ASSERT((size_t) 2 < m_field->getTargetsForWaitingPhase().size());
}

void FieldTest::getTargetsForHiddingEnemyPucks_always_numberOfPositionsBiggerThan8()
{
	CPPUNIT_ASSERT((size_t) 8 < m_field->getTargetsForHidingEnemyPucks().size());
}

void FieldTest::getTargetsForTurningToUnknownObjects_twoUnknownObjectsInRange_twoPositionsInList()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0.4));
	m_field->update();
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.2, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 0), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(1.2, 1.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(1.3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(3, 0)));

	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)2, m_field->getTargetsForTurningToUnknownObjects().size());
}

void FieldTest::getTargetsForTurningToUnknownObjects_threeUnknownObjectsInRange_threePositionsInList()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0,1), 0.8));
	m_field->update();
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.5, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.8, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.5, 1.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.8, 1)));

	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)3, m_field->getTargetsForTurningToUnknownObjects().size());
}

void FieldTest::getTargetsForTurningToUnknownObjects_zeroUnknownObjectsInRange_zeroPositionsInList()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(3,3), 0.8));
	m_field->update();
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.5, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.3, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.8, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.5, 1.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.3, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(0.8, 1)));

	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)0, m_field->getTargetsForTurningToUnknownObjects().size());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow()
{
	m_camera->setProbabilityForYellowGoal(0.82);
	m_camera->setProbabilityForBlueGoal(0.27);

	m_field->detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, m_field->getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue()
{
	m_camera->setProbabilityForYellowGoal(0.13);
	m_camera->setProbabilityForBlueGoal(0.77);

	m_field->detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, m_field->getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowAndBlueEqual_teamNotUnknown()
{
	m_camera->setProbabilityForYellowGoal(0.47);
	m_camera->setProbabilityForBlueGoal(0.47);

	m_field->detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, m_field->getOwnTeamColor());
}

void FieldTest::getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot, *m_watchMock);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot, *m_logger);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readDataFromFile("resources/testfiles/lidar_detect3.txt");
	dataAnalyser.updateSensorData();

	updateFieldForObjectsToAppear(field);
	unsigned int numberOfBorderStones;
	RobotPosition resultOrigin = field.getNewOriginFromFieldDetection(numberOfBorderStones, false);
	cout << "\nNumber Of Stones: " << numberOfBorderStones << "\nFound Origin: " << resultOrigin << endl;

	Compare compare(0.5);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(1.8, -0.5), Angle(-1.9)), resultOrigin));
}

void FieldTest::getNumberOfObjectsWithColor_noColoredObject_0()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfObjectsWithColor(FieldColorUnknown));
}

void FieldTest::getNumberOfObjectsWithColor_3YellowAnd2GreenAnd1UnknownObject_correctValues()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(2, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(3, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_field->getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorUnknown));
}

void FieldTest::getNumberOfObjectsWithColor_2BlueObjects_2()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(2, 1.8)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfObjectsWithColor(FieldColorBlue));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_field->getNumberOfObjectsWithColor(FieldColorYellow));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_field->getNumberOfObjectsWithColor(FieldColorGreen));
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_field->getNumberOfObjectsWithColor(FieldColorUnknown));
}

void FieldTest::getEstimatedNumberOfAchievedGoals_init_0()
{
	CPPUNIT_ASSERT_EQUAL((unsigned int) 0, m_field->getEstimatedNumberOfGoals());
}

void FieldTest::getEstimatedNumberOfAchievedGoals_2goals_2()
{
	m_field->increaseNumberOfEstimatedGoals();
	m_field->increaseNumberOfEstimatedGoals();

	CPPUNIT_ASSERT_EQUAL((unsigned int) 2, m_field->getEstimatedNumberOfGoals());
}

void FieldTest::getNumberOfPucksInEnemyThird_3PucksAnd2InEnemyThird_resultIs2()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.2, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 1.8), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2.35, 1.6), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.2, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.4, 1.8)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2.35, 1.6)));
	m_camera->setAllObjects(cameraObjects);

	m_lidar->setCanBeSeen(true);
	m_lidar->setCanBeSeenPartly(true);
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_field->getNumberOfPuckInEnemyThird());
}

void FieldTest::getTargetsForCollectingOnePuckNotInEnemyThird_3Objects1Unknown1InEnemyThird_numberOfPositions10()
{
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.5, 1.5), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1.7), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2.5, 2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3.5, 1.5)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, 1.7)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(2.5, 2)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT_EQUAL((size_t)10, m_field->getTargetsForCollectingOnePuckNotInEnemyThird(FieldColorYellow).size());
}

void FieldTest::isPuckOfColorInFront_noPuckInFront_resultIsFalse()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.8, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.8, 1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(!m_field->isPuckOfColorInFront(FieldColorYellow));
}

void FieldTest::isPuckOfColorInFront_puckBehind_resultIsFalse()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.5, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.5, 1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), Angle::getHalfRotation()));
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(!m_field->isPuckOfColorInFront(FieldColorYellow));
}

void FieldTest::isPuckOfColorInFront_puckInFront_resultIsTrue()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.5, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.5, 1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPuckOfColorInFront(FieldColorYellow));
}

void FieldTest::isPuckOfColorInFront_puckAlmostInFront_resultIsTrue()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.4, 1.1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.4, 1.1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPuckOfColorInFront(FieldColorYellow));
}

void FieldTest::isPuckOfColorInFront_puckAlmostInFrontAndOnePuckLeft_resultIsTrue()
{
	m_field->setTrueTeamColor(FieldColorYellow);
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), Angle::getHalfRotation()));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.4, 1.1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.3, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.4, 1.1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.3, 1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPuckOfColorInFront(FieldColorYellow));
}

void FieldTest::isPuckcolorDetected_noPucksInSector_resultIsTrue()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), Angle::getHalfRotation()));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(0.5, 1), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(3, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(0.5, 1)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPuckcolorDetected());
}

void FieldTest::isPuckcolorDetected_twoPucksWithColor_resultIsTrue()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.8, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.5, 1.2), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.8, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1.5, 1.2)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(m_field->isPuckcolorDetected());
}

void FieldTest::isPuckcolorDetected_twoPucksWithColorAndOneWithout_resultIsFlase()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(1,1), 0));
	DataAnalysis::LidarObjects lidarObjects;
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.8, 1), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.5, 1.2), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1.3, 0.8), 0.1));
	m_lidar->setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1.8, 1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1.5, 1.2)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorUnknown, Point(1.3, 0.8)));
	m_camera->setAllObjects(cameraObjects);

	updateFieldForObjectsToAppear();

	CPPUNIT_ASSERT(!m_field->isPuckcolorDetected());
}

void FieldTest::updateFieldForObjectsToAppear(FieldImpl &field)
{
	field.update();
	field.update();
}

void FieldTest::updateFieldForObjectsToDisappear(FieldImpl &field)
{
	field.update();
	field.update();
	field.update();
	field.update();
	field.update();
}

void FieldTest::updateFieldForObjectsToAppear()
{
	updateFieldForObjectsToAppear(*m_field);
}

void FieldTest::updateFieldForObjectsToDisappear()
{
	updateFieldForObjectsToDisappear(*m_field);
}
