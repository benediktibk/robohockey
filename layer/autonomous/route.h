#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTE_H

#include "common/point.h"
#include <list>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class Route
	{
	public:
		Route();

		void addPoint(const Common::Point &point);
		size_t getPointCount() const;
		bool isValid() const;
		const Common::Point& getLastPoint() const;

	private:
		std::list<Common::Point> m_points;
	};
}
}
}

#endif
