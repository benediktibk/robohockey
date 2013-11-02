#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyser;
}

namespace Autonomous
{
	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser);
		virtual ~RobotImpl();

		virtual void goTo(const Common::Point &position);

	private:
		DataAnalysis::DataAnalyser *m_dataAnalyser;
	};
}
}
}

#endif
