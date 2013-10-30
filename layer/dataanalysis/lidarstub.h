#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARSTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARSTUB_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarStub :
			public Lidar
	{
	public:
		virtual void getAllObjects() const;
	};
}
}
}

#endif
