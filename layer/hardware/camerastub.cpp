#include "layer/hardware/camerastub.h"
#include <opencv2/opencv.hpp>

using namespace RoboHockey::Layer::Hardware;

cv::Mat CameraStub::getFrame() const
{
	return cv::Mat();
}
