#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELD_H



namespace Layer
{
namespace Autonomous
{
	class Field
	{
	public:
		virtual ~Field() { }

		virtual void updateField() = 0;
	};
}
}

#endif
