#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H

#include <vector>
#include "layer/autonomous/fieldobject.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Field
	{
	public:
		virtual ~Field() { }

		virtual void update() = 0;
		virtual const std::vector<FieldObject>& getAllFieldObjects() const = 0;
		virtual const std::vector<Common::Circle>& getAllObstacles() const = 0;

		virtual bool calibratePosition() = 0;
	};
}
}
}

#endif
