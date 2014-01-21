#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDLIVEDATATEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDLIVEDATATEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class LoggerMock;
	class WatchMock;
}
namespace Layer
{
namespace DataAnalysis
{
	class OdometryMock;
	class LidarMock;
	class CameraMock;
}

namespace Autonomous
{
	class RobotMock;
	class FieldImpl;

	class FieldLiveDataTest:
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldLiveDataTest);
		CPPUNIT_TEST(update_changingData_noColoredObjectsAreLost);
		CPPUNIT_TEST(calibratePosition_goodRealWorldExample_positionIsCorrect);
		CPPUNIT_TEST(calibratePosition_worstCaseRealWorldExample_positionIsCorrect);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void update_changingData_noColoredObjectsAreLost();
		void calibratePosition_goodRealWorldExample_positionIsCorrect();
		void calibratePosition_worstCaseRealWorldExample_positionIsCorrect();

	private:
		void updateFieldForObjectsToAppear(FieldImpl &field);
		void updateFieldForObjectsToDisappear(FieldImpl &field);
		void updateFieldForObjectsToAppear();
		void updateFieldForObjectsToDisappear();

	private:
		DataAnalysis::CameraMock *m_camera;
		DataAnalysis::LidarMock *m_lidar;
		DataAnalysis::OdometryMock *m_odometry;
		RobotMock *m_robot;
		FieldImpl *m_field;
		Common::LoggerMock *m_logger;
		Common::WatchMock *m_watchMock;
	};
}
}
}

#endif
