#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYIMPL_H

#include "layer/dataanalysis/odometry.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Odometry;
}

namespace DataAnalysis
{
	class OdometryImpl :
			public Odometry
	{
	public:
		OdometryImpl(Hardware::Odometry &odometry);

		virtual void setCurrentPosition(const Common::Point &position) const;
		virtual const Common::Point& getCurrentPosition() const;

	private:
		Hardware::Odometry &m_odometry;
	};
}
}
}

#endif
