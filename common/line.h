#ifndef ROBOHOCKEY_COMMON_LINE_H
#define ROBOHOCKEY_COMMON_LINE_H

#include "common/point.h"
#include "vector"

namespace  RoboHockey
{
namespace Common
{
	class Circle;

	class Line
	{
	public:
		Line(const Point &start, const Point &end);

		std::vector<Point> getIntersectPoints(const Circle &circle) const;
		Point getPerpendicularPoint(Point point) const;
		bool isTargetPointRightOfLine(const Point &target) const;
		bool isOnePointLeftAndOneRightOfLine(const Point &one, const Point &two) const;
		void shiftParallel(const Point &point);
		Point getStart() const;
		Point getEnd() const;

	private:
		Point m_start;
		Point m_end;
	};
}
}

#endif
