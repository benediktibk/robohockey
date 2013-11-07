#ifndef ROBOHOCKEY_COMMON_ROBOTPOSITION_H
#define ROBOHOCKEY_COMMON_ROBOTPOSITION_H

#include "common/point.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition : public Point
	{
	public:
		RobotPosition();
		RobotPosition(double x, double y, double orientation);

		void setOrientation(double orientation);
		double getOrientation();

	private:
		double m_orientation;
	};
}
}
#endif
