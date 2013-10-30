#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H

namespace cv
{
class Mat;
}

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
class Camera
{
public:
	virtual ~Camera() { }

	virtual cv::Mat getFrame() = 0;
};
}
}
}

#endif
