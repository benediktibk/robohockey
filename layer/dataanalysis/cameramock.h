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

		virtual CameraObjects getAllCameraObjects() const;
		virtual bool isGoalYellow() const;

		void setIsGoalYellow(bool value);

	private:
		bool m_isGoalYellow;
	};
}
}
}

#endif
