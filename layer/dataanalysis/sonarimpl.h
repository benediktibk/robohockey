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
		SonarImpl(Hardware::Sonar &sonar);

		virtual bool isObstacleDirectInFront(double speed) const;
		virtual double getLeftFrontValue() const;
		virtual double getRightFrontValue() const;

	private:
		Hardware::Sonar &m_sonar;
	};
}
}
}

#endif
