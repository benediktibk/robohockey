#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERIMPL_H

#include "layer/dataanalysis/dataanalyser.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Robot;
}

namespace DataAnalysis
{
	class DataAnalyserImpl:
			public DataAnalyser
	{
	public:
		DataAnalyserImpl(Hardware::Robot *robot);
		virtual ~DataAnalyserImpl();

		virtual const Sonar& getSonar() const;
		virtual const Lidar& getLidar() const;
		virtual const Camera& getCamera() const;
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual void updateSensorData();

	private:
		Hardware::Robot *m_robot;
		Sonar *m_sonar;
		Lidar *m_lidar;
		Camera *m_camera;
		Odometry *m_odometry;
		Engine *m_engine;
	};
}
}
}

#endif
