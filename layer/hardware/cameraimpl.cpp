#include "layer/hardware/cameraimpl.h"

using namespace RoboHockey::Layer::Hardware;
using namespace cv;
using namespace PlayerCc;

CameraImpl::CameraImpl(PlayerCc::PlayerClient *playerClient) :
	m_camera(playerClient)
{
}

Mat* CameraImpl::getFrame() const
{
    return new Mat();
}
