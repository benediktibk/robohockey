#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTDISTANCECOMPARE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTDISTANCECOMPARE_H

#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObject;

	class FieldObjectDistanceCompare
	{
	public:
		FieldObjectDistanceCompare(const Common::Point &position);

		bool operator() (const FieldObject &one, const FieldObject &two) const;

	private:
		Common::Point m_position;
	};
}
}
}

#endif


