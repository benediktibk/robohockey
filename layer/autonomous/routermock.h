#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERMOCK_H

#include "layer/autonomous/router.h"
#include "layer/autonomous/route.h"

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
				const Common::RobotPosition &start, const Common::RobotPosition &end, const FieldPositionChecker &field,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool ignoreFinalOrientation,
				const std::vector<Common::Circle> &hardObstacles, const std::vector<Common::Circle> &softObstacles) const;
		virtual std::vector<Common::Circle> filterObstacles(const std::vector<Common::Circle> &softObstacles,
				const std::vector<Common::Circle> &hardObstacles, const Common::Point &position) const;
		void setChessMode(bool value);

		void setRoute(const Common::Point &one, const Common::Point &two, const Common::Point &three);

	private:
		bool m_chessMode;
		bool m_routeSet;
		Route m_route;
	};
}
}
}

#endif


