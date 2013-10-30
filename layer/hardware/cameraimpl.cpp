#include "layer/hardware/cameraimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace cv;
using namespace PlayerCc;

CameraImpl::CameraImpl()
{ }

Mat CameraImpl::getFrame()
{
	Mat frame;
	VideoCapture caputre;
	caputre.open(0);
	caputre >> frame;
	return frame;
}
