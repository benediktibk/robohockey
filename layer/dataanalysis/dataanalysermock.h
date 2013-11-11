#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERMOCK_H

#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/sonarmock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/enginemock.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyserMock:
			public DataAnalyser
	{
	public:
		DataAnalyserMock();

		virtual Sonar& getSonar();
		virtual const Lidar& getLidar() const;
		virtual const Camera& getCamera() const;
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual void updateSensorData();
		virtual void updateActuators();

		EngineMock& getEngineMock();
		SonarMock& getSonarMock();
		unsigned int getCallsToUpdateSensorData() const;
		unsigned int getCallsToUpdateActuators() const;

	private:
		SonarMock m_sonar;
		LidarMock m_lidar;
		CameraMock m_camera;
		OdometryMock m_odometry;
		EngineMock m_engine;
		unsigned int m_callsToUpdateSensorData;
		unsigned int m_callsToUpdateActuators;
	};
}
}
}

#endif
