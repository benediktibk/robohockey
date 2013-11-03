#ifndef ROBOHOCKEY_COMMON_CIRCLE_H
#define ROBOHOCKEY_COMMON_CIRCLE_H

#include "common/point.h"

namespace RoboHockey
{
namespace Common
{
	class Circle
	{
	public:
		Circle();
		Circle(const Point &center, double diameter);

		void setCenter(const Point &point);
		const Point& getCenter() const;
		void setDiameter(double value);
		double getDiameter() const;

	private:
		Point m_center;
		double m_diameter;
	};
}
}

#endif
