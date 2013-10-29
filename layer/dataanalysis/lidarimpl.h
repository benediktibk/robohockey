#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class LidarImpl :
		public Lidar
{
public:
	virtual void getAllObjects() const;
};
}
}
}

#endif
