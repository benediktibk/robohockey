#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDPOSITIONCHECKER_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDPOSITIONCHECKER_H

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace Autonomous
{
	class FieldPositionChecker
	{
	public:
		virtual ~FieldPositionChecker() { }

		virtual bool isPointInsideField(const Common::Point &point) const = 0;
	};
}
}
}

#endif


