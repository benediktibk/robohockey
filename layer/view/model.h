#ifndef ROBOHOCKEY_LAYER_VIEW_MODEL_H
#define ROBOHOCKEY_LAYER_VIEW_MODEL_H

#include "layer/autonomous/fieldobject.h"
#include "common/robotposition.h"
#include "common/point.h"
#include <QtCore/QObject>
#include <vector>

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Model :
			public QObject
	{
		Q_OBJECT

	public:
		Model();

		void setData(
				const std::vector<Autonomous::FieldObject> &fieldObjects,
				bool stuckAtObstacle, bool reachedTarget, const Common::RobotPosition &currentPosition,
                const Common::Point &currentTarget, bool isMoving);
		void setData(const std::vector<Common::Point> &targetPositions, bool turnAround, bool turnTo, bool stop, bool collectPuck, bool calibratePosition, bool leavePuck);
		const std::vector<Autonomous::FieldObject>& getAllFieldObjects() const;
		const std::vector<Common::Point>& getAllTargetPoints() const;
		bool stuckAtObstacle() const;
		bool reachedTarget() const;
		const Common::RobotPosition& getCurrentPosition() const;
		const Common::Point getCurrentTarget() const;
		bool isMoving() const;
        bool turnAround();
        bool getTurnAround();
        Common::Point turnToPoint(double turnToX, double turnToY);
        bool turnTo();
        bool getTurnTo();
        bool stop();
        bool getStop();
        Common::Point getTurnPoint();
		void collectPuckInFront();
		bool getCollectPuckInFront();
		void calibratePosition();
		bool getCalibratePosition();
		void leavePuckInFront();
		bool getLeavePuckInFront();

	signals:
		void targetPositionsChanged();
		void robotDataChanged();

	private:
		std::vector<Autonomous::FieldObject> m_fieldObjects;
		std::vector<Common::Point> m_targetPositions;
		bool m_stuckAtObstacle;
		bool m_reachedTarget;
		Common::RobotPosition m_currentPosition;
		Common::Point m_currentTarget;
		bool m_isMoving;
        bool m_turnAround;
        bool m_stop;
        bool m_turn;
        Common::Point m_turnToPosition;
		bool m_collectPuck;
		bool m_calibratePosition;
		bool m_leavePuck;
	};
}
}
}

#endif
