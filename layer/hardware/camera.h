#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERA_H

#include <string>

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

		virtual cv::Mat getFrame() const = 0;
		virtual bool isValid() const = 0;
		virtual void writeDataToFile(const std::string &fileName) const = 0;
	};
}
}
}

#endif
