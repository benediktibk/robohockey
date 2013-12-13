#ifndef ROBOHOCKEY_COMMON_PATH_H
#define ROBOHOCKEY_COMMON_PATH_H

#include <vector>
#include "common/point.h"

namespace  RoboHockey
{
namespace Common
{
	class Circle;
	class Angle;
	class PathIntersectPoints;
	class Line;

	class Path
	{
	public:
		Path(const Point &start, const Point &end, double width);

		bool intersectsWith(const Circle &circle) const;
		bool intersectsWith(const std::vector<Circle> &circles) const;
		bool isCircleCenterOnPath(const Circle &circle) const;
		PathIntersectPoints getIntersectPoints(const Circle &circle) const;
		Angle getAngleBetweenStartAndEnd() const;
		Point getLeftPerpendicularPoint(const Point &point) const;
		Point getRightPerpendicularPoint(const Point &point) const;
		double getDistanceToLeftPerpendicularPoint(const Point &point) const;
		double getDistanceToRightPerpendicularPoint(const Point &point) const;
		Line getCenterLine() const;

	private:
		Point m_start;
		Point m_end;
		double m_width;
	};
}
}

#endif
