#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAIMPL_H

#include "layer/dataanalysis/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class Camera;
}

namespace DataAnalysis
{
	class CameraImpl :
			public Camera
	{
	public:
		CameraImpl(const Hardware::Camera &camera);
		virtual void getColor() const;

	private:
		const Hardware::Camera &m_camera;
	};
}
}
}

#endif
