#ifndef ROBOHOCKEY_LAYER_VIEW_MODEL_H
#define ROBOHOCKEY_LAYER_VIEW_MODEL_H

#include <QtCore/QObject>
#include "layer/autonomous/fieldobject.h"
#include "common/point.h"
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

		void setData(const std::vector<Autonomous::FieldObject> &fieldObjects, bool stuckAtObstacle, bool reachedTarget, const Common::Point &currentPosition);
		void setData(const std::vector<Common::Point> &targetPositions);
		const std::vector<Autonomous::FieldObject>& getAllFieldObjects() const;
		const std::vector<Common::Point>& getAllTargetPoints() const;
		bool stuckAtObstacle() const;
		bool reachedTarget() const;
		const Common::Point& getCurrentPosition() const;

	signals:
		void targetPositionsChanged();
		void robotDataChanged();

	private:
		std::vector<Autonomous::FieldObject> m_fieldObjects;
		std::vector<Common::Point> m_targetPositions;
		bool m_stuckAtObstacle;
		bool m_reachedTarget;
		Common::Point m_currentPosition;
	};
}
}
}

#endif
