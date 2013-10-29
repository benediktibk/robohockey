#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRY_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRY_H

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace DataAnalysis
{
	class Odometry
	{
	public:
		virtual ~Odometry() { }

		virtual void setCurrentPosition(const Common::Point &position) const = 0;
		virtual const Common::Point& getCurrentPosition() const = 0;
	};
}
}
}

#endif
