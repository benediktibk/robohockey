#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDIMPL_H

#include "layer/autonomous/field.h"

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
		virtual void update();

	private:
		virtual void updateWithLidarData();
		virtual void updateWithOdometryData();


	};
}
}
}

#endif
