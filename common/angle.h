#ifndef ROBOHOCKEY_COMMON_ANGLE_H
#define ROBOHOCKEY_COMMON_ANGLE_H

#include <ostream>

namespace RoboHockey
{
namespace Common
{
	class Point;

	class Angle
	{
	public:
		Angle();
		Angle(double value);
		Angle(const Common::Point &source, const Common::Point &targetOne, const Common::Point &targetTwo);
		Angle(const Common::Point &start, const Common::Point &end);

		double getValueBetweenMinusPiAndPi() const;
		double getValueBetweenZeroAndTwoPi() const;
		void abs();

		Angle operator+(const Angle &rhs) const;
		Angle operator-(const Angle &rhs) const;
		Angle operator*(double value) const;
		Angle operator/(double value) const;

	public:
		static Angle getHalfRotation();
		static Angle getQuarterRotation();
		static Angle getFullRotation();

	private:
		void fixRange();

	private:
		double m_value;
	};
}
}

std::ostream& operator<<(std::ostream &stream, const RoboHockey::Common::Angle &angle);

#endif
