#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTOR_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTOR_H

#include <list>
#include <vector>
#include "common/point.h"
#include "common/robotposition.h"
#include "layer/autonomous/borderstonedistances.h"
#include "layer/autonomous/fielddetectionresult.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class BorderStone;

	class FieldDetector
	{
	public:
		FieldDetector();

		bool tryToDetectField(const Common::Point &currentPosition, std::vector<Common::Point> &pointsOfObjects);
		Common::Point getNewOrigin();
		double getRotation();
		unsigned int getNumberOfBorderStonesInRow();

	private:
		bool tryToFigureOutNewOrigin(BorderStone &root, const Common::Point &currentPosition);
		bool verifyNewOriginWithRoot(Common::Point &newOrigin, double rotation, BorderStone &root);
		std::vector<Common::Point> orderBorderstonesByDistanceToRoot(BorderStone &borderstone, Common::Point &root);
		bool isResultAlreadyKnown(Common::RobotPosition &newOrigin);
		FieldDetectionResult& getDetectionResultWithNewOrigin(Common::RobotPosition &newOrigin);
		bool doesConfirmedResultExist();

	private:
		const Common::Point m_currentPosition;
		std::vector<Common::Point> m_points;
		BorderStoneDistances m_distanceChecker;
		Common::Point m_newOrigin;
		double m_rotation;
		unsigned int m_maxBorderstonesArranged;
		double m_epsilonBorderStone;
		std::list<FieldDetectionResult> m_detectionResults;
	};
}
}
}

#endif
