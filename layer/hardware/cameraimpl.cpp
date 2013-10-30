#include "layer/hardware/cameraimpl.h"
#include <player-3.0/libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace cv;
using namespace PlayerCc;

CameraImpl::CameraImpl(PlayerCc::PlayerClient *playerClient) :
	m_camera(new CameraProxy(playerClient))
{ }

Mat CameraImpl::getFrame()
{
	return Mat();
}
