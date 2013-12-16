#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTE_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTE_H

#include "common/point.h"
#include "common/circle.h"
#include <list>
#include <vector>

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}
namespace Layer
{
namespace Autonomous
{
	class Route
	{
	public:
		Route();
		Route(double width);

		void addPoint(const Common::Point &point);
		void add(const Route &route);
		size_t getPointCount() const;
		bool isValid() const;
		const Common::Point& getLastPoint() const;
		const Common::Point& getNextToLastPoint() const;
		const Common::Point& getSecondPoint() const;
		const Common::Point& getFirstPoint() const;
		std::list<Common::Point> getAllPoints() const;
		void removeFirstPoint();
		double getWidth() const;
		bool intersectsWith(const std::vector<Common::Circle> &objects) const;
		void replaceFirstPoint(const Common::Point &point);
		double getLength() const;
		Common::Angle getMaximumBend(const Common::Angle &startOrientation, const Common::Angle &endOrientation) const;
		void fixRotationOfFinalStep(
				const Common::Angle &finalOrientation, const Common::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation);

	public:
		static Common::Angle calculateNecessaryRotation(
				const Common::RobotPosition &start, const Common::Point &end);
		static Common::Point calculateMaximumRotatedNextPoint(
				const Common::RobotPosition &start, const Common::Angle &desiredRotation,
				const Common::Angle &maximumRotation, double minimumStepAfterMaximumRotation);

	private:
		std::list<Common::Point> m_points;
		double m_width;
	};
}
}
}

#endif
