#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H

#include <vector>
#include "common/compare.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	enum BorderStoneFieldDistance
	{
		BorderStoneFieldDistanceRoot,
		BorderStoneFieldDistanceA,
		BorderStoneFieldDistanceB,
		BorderStoneFieldDistanceC,
		BorderStoneFieldDistanceD,
		BorderStoneFieldDistanceFalse
	};

	class BorderStoneDistances
	{
	public:
		BorderStoneDistances(double epsilon);

		double getStandardFieldDistance(BorderStoneFieldDistance distanceType) const;
		bool isDistanceStandardDistance(double distance) const;
		BorderStoneFieldDistance getStandardDistanceType(double distance) const;
		bool verifyPoints(std::vector<Common::Point> &points);

	private:
		Common::Compare m_compare;
	};
}
}
}


#endif
