#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_SONARSTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_SONARSTUB_H

#include "layer/dataanalysis/sonar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class SonarStub :
		public Sonar
{
public:
	virtual double getMinimumDistance() const;
};
}
}
}

#endif
