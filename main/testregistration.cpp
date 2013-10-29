#include "common/comparetest.h"
#include "common/pointtest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "threading/locktest.h"
#include "layer/dataanalysis/dataanalysertest.h"
#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/odometrytest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::LockTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::DataAnalyserTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::CameraTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::EngineTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::LidarTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Layer::DataAnalysis::OdometryTest);
