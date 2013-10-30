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

		virtual bool isObstacleDirectInFront() const = 0;
	};
}
}
}

#endif
