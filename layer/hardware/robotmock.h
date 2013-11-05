#ifndef ROBOHOCKEY_LAYER_HARDWARE_ROBOTMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ROBOTMOCK_H

#include "layer/hardware/robotstub.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class RobotMock :
			public RobotStub
	{
	public:
		RobotMock();

		virtual Sonar& getSonar();
		virtual Lidar &getLidar();
		virtual Camera& getCamera();
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual void updateSensorData();	
		virtual bool isValid() const;

		unsigned int getCallsToGetSonar() const;
		unsigned int getCallsToGetLidar() const;
		unsigned int getCallsToGetCamera() const;
		unsigned int getCallsToGetOdometry() const;
		unsigned int getCallsToGetEngine() const;
		unsigned int getCallsToGetSensorData() const;

	private:
		unsigned int m_callsToGetSonar;
		unsigned int m_callsToGetLidar;
		unsigned int m_callsToGetCamera;
		unsigned int m_callsToGetOdometry;
		unsigned int m_callsToGetEngine;
		unsigned int m_callsToGetSensorData;
	};
}
}
}

#endif
