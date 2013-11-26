#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAMOCK_H

#include "layer/dataanalysis/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraMock :
			public Camera
	{
	public:
		CameraMock();

		virtual CameraObjects getAllCameraObjects(const Common::RobotPosition &position);
		virtual bool isGoalYellow();

		void setIsGoalYellow(bool value);

		void setAllObjects(const CameraObjects &objects);

	private:
		bool m_isGoalYellow;
		CameraObjects m_objects;
	};
}
}
}

#endif
