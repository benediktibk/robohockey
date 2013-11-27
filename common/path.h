#ifndef ROBOHOCKEY_COMMON_PATH_H
#define ROBOHOCKEY_COMMON_PATH_H

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

	private:
		Point m_start;
		Point m_end;
		double m_width;
	};
}
}

#endif
