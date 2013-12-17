#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERMOCK_H

#include "layer/autonomous/router.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouterMock :
			public Router
	{
	public:
		RouterMock();

		virtual Route calculateRoute(
				const Common::RobotPosition &start, const Common::RobotPosition &end, const Field &field,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation,
				bool ignoreSoftObstacles, bool ignoreFinalOrientation) const;
		virtual std::vector<Common::Circle> filterObstacles(const std::vector<Common::Circle> &softObstacles,
				const std::vector<Common::Circle> &hardObstacles, const Common::Point &position) const;
		void setChessMode(bool value);

	private:
		bool m_chessMode;
	};
}
}
}

#endif


