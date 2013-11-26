#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDMOCK_H

#include "layer/autonomous/field.h"

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{

	class FieldMock : public Field
	{
	public:
		FieldMock();

		virtual void update();
		virtual std::vector<FieldObject> &getAllFieldObjects();

		virtual bool calibratePosition();

		void setFieldObjects(std::vector<FieldObject> &objects);

	private:
		std::vector<FieldObject> m_objects;
	};
}
}
}

#endif
