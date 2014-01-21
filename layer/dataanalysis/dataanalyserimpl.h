#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSERIMPL_H

#include "layer/dataanalysis/dataanalyser.h"

namespace RoboHockey
{
namespace Common
{
	class Watch;
	class Logger;
}
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
		DataAnalyserImpl(Hardware::Robot *robot, const Common::Watch &watch, Common::Logger &logger);
		virtual ~DataAnalyserImpl();

		virtual Sonar& getSonar();
		virtual const Lidar& getLidar() const;
		virtual Camera& getCamera();
		virtual Odometry& getOdometry();
		virtual Engine& getEngine();
		virtual void updateSensorData();
		virtual void updateActuators();

	private:
		// forbid copies
		DataAnalyserImpl(const DataAnalyserImpl &robot);
		void operator=(const DataAnalyserImpl &robot);

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
