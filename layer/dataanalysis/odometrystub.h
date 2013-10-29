#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYSTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYSTUB_H

#include "layer/dataanalysis/odometry.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class OdometryStub :
		public Odometry
{
public:
	virtual void setCurrentPosition(const Common::Point &position) const;
	virtual const Common::Point& getCurrentPosition() const;
};
}
}
}

#endif
