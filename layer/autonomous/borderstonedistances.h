#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONEDISTANCES_H


namespace RoboHockey
{
namespace Common
{
	class Compare;
}
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
		~BorderStoneDistances();

		double getStandardFieldDistance(BorderStoneFieldDistance distanceType) const;
		bool distanceIsStandardDistance(double distance) const;
		BorderStoneFieldDistance checkForStandardDistance(double distance) const;

	private:
		Common::Compare *m_compare;
	};
}
}
}


#endif
