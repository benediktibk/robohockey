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
						 IntersectTypeFromStart,
						 IntersectTypeNoIntersect
					   };

public:
	PathIntersectPoints(std::vector<Point> intersectPoints, IntersectType intersectFrom);

	std::vector<Point> getIntersectPoints();
	IntersectType getIntersectTypeFrom();
	std::size_t getIntersectPointsCount();
	Point front();
	Point back();

private:
	std::vector<Point> m_intersectPoints;
	IntersectType m_intersectFrom;
	
};
}
}

#endif // ROBOHOCKEY_COMMON_PATHINTERSECTPOINTS_H


