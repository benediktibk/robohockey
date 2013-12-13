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
		virtual double getProbabilityForCollectedYellowPuck();
		virtual double getProbabilityForCollectedBluePuck();

		void setProbabilityForYellowGoal(double value);
		void setProbabilityForBlueGoal(double value);
		void setProbabilityForCollectedYellowPuck(double value);
		void setProbabilityForCollectedBluePuck(double value);

		void setAllObjects(const CameraObjects &objects);

	private:
		double m_probabilityForYellow;
		double m_probabilityForBlue;
		double m_probabilityForYellowPuck;
		double m_probabilityForBluePuck;
		CameraObjects m_objects;
	};
}
}
}

#endif
