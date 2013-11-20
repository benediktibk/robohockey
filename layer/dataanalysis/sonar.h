#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONAR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONAR_H

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class Sonar
	{
	public:
		virtual ~Sonar() { }

		virtual bool isObstacleDirectInFront(double minimumDistanceToObstacle) = 0;
	};
}
}
}

#endif
