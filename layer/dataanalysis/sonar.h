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

		virtual bool isObstacleDirectInFront(double speed) const = 0;
		virtual double getLeftFrontValue() const = 0;
		virtual double getRightFrontValue() const = 0;
	};
}
}
}

#endif
