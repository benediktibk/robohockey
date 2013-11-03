#ifndef ROBOHOCKEY_COMMON_RECTANGLE_H
#define ROBOHOCKEY_COMMON_RECTANGLE_H

#include "common/point.h"

namespace RoboHockey
{
namespace Common
{
	class Compare;
	class Circle;

	class Rectangle
	{
	public:
		Rectangle(const Point &one, const Point &two);

		const Point &getLeftLower() const;
		const Point &getRightUpper() const;
		double getWidth() const;
		double getHeight() const;
		bool isInside(const Point &point, const Compare &compare) const;
		bool overlapsApproximately(const Circle &circle, const Compare &compare) const;
		bool overlaps(const Rectangle &rectangle, const Compare &compare) const;

	private:
		Point m_leftLower;
		Point m_rightUpper;
	};
}
}

#endif
