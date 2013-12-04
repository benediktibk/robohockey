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
		virtual void update();
		virtual bool tryToFindField();
        virtual std::vector<FieldObject> getAllFieldObjects();
        virtual int achievedGoals();
	};
}
}
}

#endif
