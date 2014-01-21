#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class WatchMock;
	class LoggerMock;
}

namespace Layer
{
namespace Hardware
{
	class RobotMock;
}

namespace DataAnalysis
{
	class DataAnalyserImpl;

	class DataAnalyserTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(DataAnalyserTest);
		CPPUNIT_TEST(constructor_mockRobot_atLeastOneCallToGetSonar);
		CPPUNIT_TEST(constructor_mockRobot_atLeastOneCallToGetLidar);
		CPPUNIT_TEST(constructor_mockRobot_atLeastOneCallToGetCamera);
		CPPUNIT_TEST(constructor_mockRobot_atLeastOneCallToGetOdometry);
		CPPUNIT_TEST(constructor_mockRobot_atLeastOneCallToGetEngine);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void constructor_mockRobot_atLeastOneCallToGetSonar();
		void constructor_mockRobot_atLeastOneCallToGetLidar();
		void constructor_mockRobot_atLeastOneCallToGetCamera();
		void constructor_mockRobot_atLeastOneCallToGetOdometry();
		void constructor_mockRobot_atLeastOneCallToGetEngine();

	private:
		Hardware::RobotMock *m_hardwareRobot;
		DataAnalyserImpl *m_dataAnalyser;
		Common::WatchMock *m_watch;
		Common::LoggerMock *m_logger;
	};
}
}
}

#endif
