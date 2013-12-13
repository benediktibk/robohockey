#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECT_H

#include "common/circle.h"
#include "common/fieldcolor.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObject
	{
	public:
		FieldObject(const Common::Circle &circle, Common::FieldColor color);

		const Common::Circle &getCircle() const;
		Common::FieldColor getColor() const;
		void setColor(Common::FieldColor color);
		void setCircle(const Common::Circle &circle);

	private:
		Common::Circle m_circle;
		Common::FieldColor m_color;
	};
}
}
}


#endif
