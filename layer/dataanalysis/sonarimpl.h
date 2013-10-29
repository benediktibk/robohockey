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
	SonarImpl(const Hardware::Sonar &sonar);

	virtual double getMinimumDistance() const;

private:
	const Hardware::Sonar &m_sonar;
};
}
}
}

#endif
