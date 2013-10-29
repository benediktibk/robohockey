#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYIMPL_H

#include "layer/dataanalysis/odometry.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class OdometryImpl :
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
