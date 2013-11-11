#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYMOCK_H

#include "layer/dataanalysis/odometry.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class OdometryMock :
			public Odometry
	{
	public:
		virtual void setCurrentPosition(const Common::Point &position, double orientation);
		virtual Common::Point getCurrentPosition() const;
		virtual double getCurrentOrientation() const;

	private:
		Common::Point m_position;
		double m_orientation;
	};
}
}
}

#endif
