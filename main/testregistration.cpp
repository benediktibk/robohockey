#include "common/comparetest.h"
#include "common/pointtest.h"
#include "threading/threadtest.h"
#include "threading/mutextest.h"
#include "threading/signaltest.h"
#include "threading/locktest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::CompareTest);
CPPUNIT_TEST_SUITE_REGISTRATION(RoboHockey::Common::PointTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::ThreadTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::MutexTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::SignalTest);
CPPUNIT_TEST_SUITE_REGISTRATION(Threading::LockTest);
