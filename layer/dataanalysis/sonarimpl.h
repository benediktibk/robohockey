#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONARIMPL_H

#include "layer/dataanalysis/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Sonar;
}

namespace DataAnalysis
{
	class SonarImpl :
			public Sonar
	{
	public:
		SonarImpl(Hardware::Sonar &sonar, double minimumDistanceToObstacle);

		virtual bool isObstacleDirectInFront();

	private:
		Hardware::Sonar &m_sonar;
		const double m_distanceOfSensorsToMiddleOfRobot;
		const double m_minimumDistanceToObstacle;
		const double m_minimumDistanceWithAngst;
	};
}
}
}

#endif
