#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTCOLORCOMPARE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTCOLORCOMPARE_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObject;

	class FieldObjectColorCompare
	{
	public:
		bool operator() (const FieldObject &one, const FieldObject &two) const;
	};
}
}
}

#endif


