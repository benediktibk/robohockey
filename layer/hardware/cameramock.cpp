#include "layer/hardware/cameramock.h"
#include <opencv2/opencv.hpp>

using namespace RoboHockey::Layer::Hardware;

CameraMock::CameraMock() :
	m_callsToGetFrame(0)
{ }

cv::Mat CameraMock::getFrame()
{
	++m_callsToGetFrame;
	return cv::Mat();
}

unsigned int CameraMock::getCallsToGetFrame() const
{
	return m_callsToGetFrame;
}
