#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H

#include "common/circle.h"
#include "layer/autonomous/fieldobjectcolor.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObject
	{
	public:
		FieldObject(const Common::Circle &circle, FieldObjectColor color);

		const Common::Circle &getCircle() const;
		FieldObjectColor getColor() const;

	private:
		Common::Circle m_circle;
		FieldObjectColor m_color;
	};
}
}
}


#endif
