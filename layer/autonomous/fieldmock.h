#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H

#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{

	class FieldMock :
			public Field
	{
	public:
		FieldMock();

		virtual void update();
		virtual const std::vector<FieldObject>& getAllFieldObjects() const;
		virtual const std::vector<Common::Circle>& getAllObstacles() const;

		virtual bool calibratePosition();

		void setFieldObjects(const std::vector<FieldObject> &objects);
		void setObstacles(const std::vector<Common::Circle> &obstacles);

	private:
		std::vector<FieldObject> m_objects;
		std::vector<Common::Circle> m_obstacles;
	};
}
}
}

#endif
