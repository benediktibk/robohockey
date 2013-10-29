#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONARIMPL_H

#include "layer/dataanalysis/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class SonarImpl :
		public Sonar
{
public:
	virtual double getMinimumDistance() const;
};
}
}
}

#endif
