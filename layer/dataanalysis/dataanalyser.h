#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSER_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_DATAANALYSER_H

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class Camera;
	class Engine;
	class Lidar;
	class Odometry;
	class Sonar;

	class DataAnalyser
	{
	public:
		virtual ~DataAnalyser() { }

		virtual Sonar& getSonar() = 0;
		virtual const Lidar& getLidar() const = 0;
		virtual Camera& getCamera() = 0;
		virtual Odometry& getOdometry() = 0;
		virtual Engine& getEngine() = 0;
		virtual void updateSensorData() = 0;
		virtual void updateActuators() = 0;
	};
}
}
}

#endif
