#include "common/comparetest.h"
#include "common/pointtest.h"
#include "common/discretefunctiontest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "threading/locktest.h"
#include "layer/dataanalysis/dataanalysertest.h"
#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/lidarobjecttest.h"
#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/odometrytest.h"
#include "layer/dataanalysis/sonartest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::DiscreteFunctionTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Threading::LockTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::DataAnalyserTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::EngineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarObjectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::OdometryTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::SonarTest);
