#ifndef ROBOHOCKEY_COMMON_ROBOTPOSITION_H
#define ROBOHOCKEY_COMMON_ROBOTPOSITION_H

#include "common/point.h"
#include "common/angle.h"
#include <ostream>

namespace RoboHockey
{
namespace Common
{
	class RobotPosition
	{
	public:
		RobotPosition();
		RobotPosition(const Point &point, const Angle &orientation);

		void setOrientation(const Angle &orientation);
		const Angle& getOrientation() const;
		void setPosition(const Point &position);
		const Point& getPosition() const;
		double distanceTo(const RobotPosition &point) const;
		void read(const std::string &data);
		Angle getRelativeOrientationTo(const Point &point) const;

		bool operator ==(const RobotPosition &position) const;
		RobotPosition operator*(double value) const;
		RobotPosition operator/(double value) const;
		RobotPosition operator+(const RobotPosition &point) const;
		RobotPosition operator-(const RobotPosition &point) const;
		void operator*=(double value);
		operator Point() const;

	private:
		Point m_position;
		Angle m_orientation;
	};
}
}

std::ostream& operator<<(std::ostream &stream, const RoboHockey::Common::RobotPosition &point);

#endif
