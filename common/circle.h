#ifndef ROBOHOCKEY_COMMON_CIRCLE_H
#define ROBOHOCKEY_COMMON_CIRCLE_H

#include "common/point.h"
#include "common/rectangle.h"
#include <vector>

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
		bool overlapsWith(const std::vector<Circle> &circles) const;
		std::vector<Common::Point> getIntersectionPoints(const Circle &circle) const;
		bool isOnCircle(const Point &point, const Compare &compare) const;
		bool isInside(const Point &point) const;

		bool operator==(const Circle &circle) const;

	private:
		Point m_center;
		double m_diameter;
	};
}
}

#endif
