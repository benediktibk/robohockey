#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H

#include "layer/hardware/camera.h"
#include <opencv2/opencv.hpp>
#include <player-3.0/libplayerc++/playerc++.h>

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class CameraImpl :
		public Camera
{
public:
	CameraImpl(PlayerCc::PlayerClient *playerClient);

	virtual cv::Mat getFrame() const;

private:
	PlayerCc::CameraProxy m_camera;
};
}
}
}

#endif
