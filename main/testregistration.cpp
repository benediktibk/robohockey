#include "common/comparetest.h"
#include "common/watchtest.h"
#include "common/pointtest.h"
#include "common/discretefunctiontest.h"
#include "common/rectangletest.h"
#include "common/circletest.h"
#include "common/robotpositiontest.h"
#include "common/angletest.h"
#include "common/quadraticequationtest.h"
#include "common/pathtest.h"
#include "common/linetest.h"
#include "common/pathintersectpointstest.h"
#include "common/signumtest.h"
#include "common/randomdecisiontest.h"
#include "common/pointdistancecomparetest.h"
#include "common/timesmoothedbooleantest.h"
#include "common/stopwatchtest.h"
#include "common/loggertest.h"
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
#include "layer/dataanalysis/cameraobjecttest.h"
#include "layer/dataanalysis/cameraobjectstest.h"
#include "layer/autonomous/robottest.h"
#include "layer/autonomous/fieldobjecttest.h"
#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/borderstonetest.h"
#include "layer/autonomous/borderstonedistancestest.h"
#include "layer/autonomous/fielddetectortest.h"
#include "layer/autonomous/routetest.h"
#include "layer/autonomous/routertest.h"
#include "layer/autonomous/fieldobjectdistancecomparetest.h"
#include "layer/autonomous/routelengthcomparetest.h"
#include "layer/autonomous/routingobstacletest.h"
#include "layer/autonomous/routingresulttest.h"
#include "layer/autonomous/fielddetectionresulttest.h"
#include "layer/view/modeltest.h"
#include "layer/strategy/common/statemachinetest.h"
#include "layer/strategy/common/drivetostatetest.h"
#include "layer/strategy/common/colordependentpucktargetfetchertoachivegoalstest.h"
#include "layer/strategy/common/colordependentpucktargetfetchertohidepuckstest.h"
#include "layer/strategy/common/statetest.h"
#include "layer/strategy/mainstatemachine/initialstatetest.h"
#include "layer/strategy/mainstatemachine/calibratetest.h"
#include "layer/strategy/mainstatemachine/achievegoalstest.h"
#include "layer/strategy/mainstatemachine/hideenemypuckstest.h"
#include "layer/strategy/mainstatemachine/pausetest.h"
#include "layer/strategy/mainstatemachine/drivetofinalpositiontest.h"
#include "layer/strategy/fielddetectionstatemachine/initialstatetest.h"
#include "layer/strategy/fielddetectionstatemachine/detectfieldtest.h"
#include "layer/strategy/fielddetectionstatemachine/checkgoalcolortest.h"
#include "layer/strategy/fielddetectionstatemachine/turnangletest.h"
#include "layer/strategy/fielddetectionstatemachine/calibrationfinishedtest.h"
#include "layer/strategy/drivepuckstatemachine/initialstatetest.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstatetest.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstatetest.h"
#include "layer/strategy/common/waitcyclesstatetest.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstatetest.h"
#include "main/inputargumentparsertest.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstatetest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::WatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::DiscreteFunctionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::RectangleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CircleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::RobotPositionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::AngleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PathTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::LineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PathIntersectPointsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::QuadraticEquationTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::SignumTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::RandomDecisionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointDistanceCompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::TimeSmoothedBooleanTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::StopWatchTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::LoggerTest);
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
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraObjectsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RobotTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::BorderStoneTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::BorderStoneDistancesTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldDetectorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RouteTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RouterTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldObjectDistanceCompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RouteLengthCompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RoutingObstacleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::RoutingResultTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Autonomous::FieldDetectionResultTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::View::ModelTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::StateMachineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::DriveToStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::ColorDependentPuckTargetFetcherToAchiveGoalsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::ColorDependentPuckTargetFetcherToHidePucksTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::StateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::Common::WaitCyclesStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::InitialStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::CalibrateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::AchieveGoalsTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::HideEnemyPucksTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::PauseTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::MainStateMachine::DriveToFinalPositionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::FieldDetectionStateMachine::InitialStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::FieldDetectionStateMachine::DetectFieldTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::FieldDetectionStateMachine::CheckGoalColorTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::FieldDetectionStateMachine::TurnAngleTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::FieldDetectionStateMachine::CalibrationFinishedTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::InitialStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::FindPuckStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::CollectPuckStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::DrivePuckToPositionStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::DriveToCollectPuckStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::LeavePuckStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::DrivePuckToEnemyThirdStateTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Main::InputArgumentParserTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::Strategy::DrivePuckStateMachine::VerifyPuckStateTest);

