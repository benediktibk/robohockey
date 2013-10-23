#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAIMPL_H

#include "layer/hardware/camera.h"
#include <opencv2/opencv.hpp>

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
    virtual cv::Mat* getFrame() const;
};
}
}
}

#endif
