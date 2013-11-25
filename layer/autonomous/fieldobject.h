#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H

#include "common/circle.h"
#include "common/fieldobjectcolor.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObject
	{
	public:
		FieldObject(const Common::Circle &circle, Common::FieldObjectColor color);

		const Common::Circle &getCircle() const;
		Common::FieldObjectColor getColor() const;
		void setColor(Common::FieldObjectColor color);
		void setCircle(const Common::Circle &circle);

	private:
		Common::Circle m_circle;
		Common::FieldObjectColor m_color;
	};
}
}
}


#endif
