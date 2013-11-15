#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTOR_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTOR_H

#include <vector>
#include "common/point.h"
#include "layer/autonomous/borderstonedistances.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldDetector
	{
	public:
		FieldDetector(std::vector<Common::Point> &points);

		bool tryToDetectField();
		Common::Point getNewOrigin();
		double getRotation();

	private:
		std::vector<Common::Point> m_points;
		BorderStoneDistances m_distanceChecker;
		Common::Point m_newOrigin;
		double m_rotation;
	};
}
}
}

#endif
