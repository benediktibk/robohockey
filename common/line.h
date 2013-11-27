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

		std::vector<Common::Point> getIntersectPoints(const Circle &circle) const;

	private:
		const Common::Point m_start;
		const Common::Point m_end;
	};
}
}

#endif
