#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONE_H

#include "common/point.h"
#include <vector>
#include "layer/autonomous/borderstonedistances.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class BorderStone:
			public Common::Point
	{
	public:
		BorderStone(Common::Point &father, BorderStoneFieldDistance distanceToFather, BorderStoneDistances &distances, Point &point);
		virtual void searchNeighbourBorderStones(std::vector<Point> &candidates);
		virtual std::vector<BorderStone> &getAllChildren();

	private:
		std::vector<BorderStone> m_children;
		BorderStoneDistances m_distances;
		Common::Point m_father;
		BorderStoneFieldDistance m_distanceToFather;

	};
}
}
}

#endif
