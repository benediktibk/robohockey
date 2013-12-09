#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTELENGTHCOMPARE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTELENGTHCOMPARE_H

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Route;

	class RouteLengthCompare
	{
	public:
		RouteLengthCompare();

		bool operator() (const Route &one, const Route &two) const;
	};
}
}
}

#endif


