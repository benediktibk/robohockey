#ifndef ROBOHOCKEY_COMMON_PATH_H
#define ROBOHOCKEY_COMMON_PATH_H

#include <vector>
#include "common/point.h"

namespace  RoboHockey
{
namespace Common
{
	class Circle;

	class Path
	{
	public:
		Path(const Point &start, const Point &end, double width);

		bool intersectsWith(const Circle &circle) const;
		bool intersectsWith(const std::vector<Circle> &circles) const;
		bool isCircleCenterOnPath(const Circle &circle) const;
		std::vector<Common::Point> getIntersectPoints(const Circle &circle) const;

	private:
		Point m_start;
		Point m_end;
		double m_width;
	};
}
}

#endif
