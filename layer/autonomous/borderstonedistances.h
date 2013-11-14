#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H


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
		BorderStoneDistances();
		double getStandardFieldDistance(BorderStoneFieldDistance distanceType) const;
		BorderStoneFieldDistance checkForStandardDistance() const;
	};
}
}
}


#endif
