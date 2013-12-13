#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREE_H

#include "extern/angelina/teamcolor.h"
#include "common/fieldcolor.h"

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace Strategy
{
namespace Common
{
	class Referee
	{
	public:
		virtual ~Referee() { }

		virtual void reportReady() = 0;
		virtual void reportDone() = 0;
		virtual void sendAlive() = 0;
		virtual void tellTeamColor(RoboHockey::Common::FieldColor color) = 0;
		virtual void reportGoal() = 0;
		virtual void tellEgoPos(const RoboHockey::Common::Point &position) = 0;
		virtual bool detectionStart() = 0;
		virtual bool gameStart() = 0;
		virtual bool gameOver() = 0;
		virtual RoboHockey::Common::FieldColor trueColorOfTeam() = 0;
		virtual bool stopMovement() = 0;
		virtual bool isValid() = 0;

	};
}
}
}
}

#endif
