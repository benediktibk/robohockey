#ifndef ROBOHOCKEY_COMMON_ANGLE_H
#define ROBOHOCKEY_COMMON_ANGLE_H

namespace RoboHockey
{
namespace Common
{
	class Angle
	{
	public:
		Angle();
		Angle(double value);

		double getValueBetweenMinusPiAndPi() const;
		double getValueBetweenZeroAndTwoPi() const;

		Angle operator+(const Angle &rhs) const;
		Angle operator-(const Angle &rhs) const;

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


#endif
