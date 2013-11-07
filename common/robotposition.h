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
		RobotPosition(double x, double y);
		RobotPosition(double x, double y, double orientation);

		void setOrientation(double orientation);
		double getOrientation() const;

		bool operator ==(const RobotPosition &position) const;
		RobotPosition operator*(double value) const;
		RobotPosition operator/(double value) const;
		RobotPosition operator+(const RobotPosition &point) const;
		RobotPosition operator-(const RobotPosition &point) const;
		void operator*=(double value);
		double distanceTo(const RobotPosition &point) const;


	private:
		double m_orientation;
	};
}
}
#endif
