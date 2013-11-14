#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYMOCK_H

#include "layer/dataanalysis/odometry.h"
#include "common/robotposition.h"

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
		virtual void setCurrentPosition(const Common::RobotPosition &position);
		virtual Common::RobotPosition getCurrentPosition() const;

	private:
		Common::RobotPosition m_position;
	};
}
}
}

#endif
