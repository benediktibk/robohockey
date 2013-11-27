#include "common/comparetest.h"
#include "common/watchtest.h"
#include "common/pointtest.h"
#include "common/discretefunctiontest.h"
#include "common/rectangletest.h"
#include "common/circletest.h"
#include "common/robotpositiontest.h"
#include "common/angletest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "threading/locktest.h"
#include "layer/dataanalysis/dataanalysertest.h"
#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/lidarobjecttest.h"
#include "layer/dataanalysis/lidarobjectdistancecomparatortest.h"
#include "layer/dataanalysis/lidarobjectstest.h"
#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarinternalobjecttest.h"
#include "layer/dataanalysis/odometrytest.h"
#include "layer/dataanalysis/sonartest.h"
#include "layer/dataanalysis/speedtresholdertest.h"
#include "layer/autonomous/robottest.h"
#include "layer/autonomous/fieldobjecttest.h"
#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/borderstonetest.h"
#include "layer/autonomous/borderstonedistancestest.h"
#include "layer/autonomous/fielddetectortest.h"
#include "layer/view/modeltest.h"
#include "layer/view/robotdrivertest.h"
#include "layer/dataanalysis/cameraobjecttest.h"
#include "layer/dataanalysis/cameraobjectstest.h"
#include "layer/strategy/statemachinetest.h"
#include "layer/strategy/initialstatetest.h"
#include "common/pathtest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::WatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::DiscreteFunctionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::RectangleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CircleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::RobotPositionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::AngleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PathTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::LockTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::DataAnalyserTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::EngineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarObjectDistanceComparatorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarObjectsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::OdometryTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::SonarTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::SpeedTresholderTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarInternalObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RobotTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::BorderStoneTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::BorderStoneDistancesTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldDetectorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::View::ModelTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::View::RobotDriverTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraObjectsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::StateMachineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::InitialStateTest);

