#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "field.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarImpl;
	class SonarImpl;
	class OdometryImpl;
	class CameraImpl;
}

namespace Autonomous
{
	class FieldImpl :
			public Field
	{
	public:
		FieldImpl();
	};
}
}
}

#endif
