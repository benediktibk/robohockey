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
		virtual Route calculateRoute(const Common::Point &start, const Common::Point &end, const Field &field) const;
	};
}
}
}

#endif


