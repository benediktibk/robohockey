#include "layer/hardware/cameraimpl.h"

using namespace RoboHockey::Layer::Hardware;
using namespace cv;

Mat* CameraImpl::getFrame() const
{
    return new Mat();
}
