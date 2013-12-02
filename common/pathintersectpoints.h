#ifndef ROBOHOCKEY_COMMON_PATHINTERSECTPOINTS_H
#define ROBOHOCKEY_COMMON_PATHINTERSECTPOINTS_H

#include <vector>
#include "common/point.h"

namespace RoboHockey
{
namespace Common
{
class PathIntersectPoints
{
public:
	enum IntersectType { IntersectTypeFromLeft,
						 IntersectTypeFromRight,
						 IntersectTypeFromEnd,
						 IntersectTypeFromStart
					   };

public:
	PathIntersectPoints(std::vector<Common::Point> intersectPoints, IntersectType intersectFrom);

	std::vector<Common::Point> getIntersectPoints();
	IntersectType getIntersectTypeFrom();
	std::size_t getIntersectPointsCount();

private:
	std::vector<Common::Point> m_intersectPoints;
	IntersectType m_intersectFrom;
	
};
}
}

#endif // ROBOHOCKEY_COMMON_PATHINTERSECTPOINTS_H


