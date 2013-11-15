#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRY_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRY_H

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}

namespace Layer
{
namespace DataAnalysis
{
	class Odometry
	{
	public:
		virtual ~Odometry() { }

		virtual void setCurrentPosition(const Common::RobotPosition &position) = 0;
		virtual Common::RobotPosition getCurrentPosition() const = 0;
	};
}
}
}

#endif
