#ifndef ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_ODOMETRYIMPL_H

#include "layer/hardware/odometry.h"
#include "common/robotposition.h"

namespace PlayerCc
{
	class PlayerClient;
	class Position2dProxy;
}

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class OdometryImpl :
			public Odometry
	{
	public:
		OdometryImpl(PlayerCc::PlayerClient *playerClient);
		~OdometryImpl();

		virtual void setCurrentPosition(const Common::RobotPosition &position);
		virtual Common::RobotPosition getCurrentPosition() const;
		virtual void writeDataToFile(const std::string &fileName) const;

	private:
		OdometryImpl(const OdometryImpl &odometry);
		void operator=(const OdometryImpl &odometry);
		const Common::RobotPosition getGlobalPositionAfterPlayerOffset() const;

	private:
		PlayerCc::Position2dProxy *m_odometry;
		Common::RobotPosition m_playerOffset;
		Common::RobotPosition m_ownOffset;
	};
}
}
}

#endif
