#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARIMPL_H

#include "layer/dataanalysis/lidar.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Lidar;
}

namespace DataAnalysis
{
	class LidarImpl :
			public Lidar
	{
	public:
		LidarImpl(const Hardware::Lidar &lidar);

		virtual void getAllObjects() const;

	private:
		const Hardware::Lidar &m_lidar;
	};
}
}
}

#endif
