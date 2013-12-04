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
		virtual double getProbabilityForYellowGoal();
		virtual double getProbabilityForBlueGoal();

		void setProbabilityForYellowGoal(bool value);
		void setProbabilityForBlueGoal(bool value);

		void setAllObjects(const CameraObjects &objects);

	private:
		double m_probabilityForYellow;
		double m_probabilityForBlue;
		CameraObjects m_objects;
	};
}
}
}

#endif
