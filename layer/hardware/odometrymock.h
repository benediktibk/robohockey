#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYMOCK_H

#include "layer/hardware/odometry.h"
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class OdometryMock :
			public Odometry
	{
	public:
		OdometryMock();

		virtual void setCurrentPosition(const Common::RobotPosition &position);
		virtual Common::RobotPosition getCurrentPosition() const;
		virtual void writeDataToFile(const std::string &fileName) const;

		unsigned int getCallsToSetCurrentPosition() const;
		void readDataFromFile(const std::string &fileName);

	private:
		unsigned int m_callsToSetCurrentPosition;
		Common::RobotPosition m_currentPosition;
	};
}
}
}

#endif
