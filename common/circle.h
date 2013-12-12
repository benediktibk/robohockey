#ifndef ROBOHOCKEY_COMMON_CIRCLE_H
#define ROBOHOCKEY_COMMON_CIRCLE_H

#include "common/point.h"
#include "common/rectangle.h"

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
		Rectangle getBoundingRectangle() const;
		double getDistanceTo(const Common::Point &position) const;
		bool overlapsWith(const Circle &circle) const;

	private:
		Point m_center;
		double m_diameter;
	};
}
}

#endif
