#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERSTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERSTUB_H

#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/sonarstub.h"
#include "layer/dataanalysis/lidarstub.h"
#include "layer/dataanalysis/camerastub.h"
#include "layer/dataanalysis/odometrystub.h"
#include "layer/dataanalysis/enginestub.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyserStub:
			public DataAnalyser
	{
	public:
		virtual const Sonar& getSonar() const;
		virtual const Lidar& getLidar() const;
		virtual const Camera& getCamera() const;
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual void updateSensorData();

	private:
		SonarStub m_sonar;
		LidarStub m_lidar;
		CameraStub m_camera;
		OdometryStub m_odometry;
		EngineStub m_engine;
	};
}
}
}

#endif
