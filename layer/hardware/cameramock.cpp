#include "layer/hardware/cameramock.h"
#include <opencv2/opencv.hpp>

using namespace RoboHockey::Layer::Hardware;
using namespace std;
using namespace cv;

CameraMock::CameraMock() :
	m_callsToGetFrame(0),
	m_testpicture(new Mat(240, 320, CV_8UC3))
{ }

CameraMock::CameraMock(std::string filename) :
	m_callsToGetFrame(0),
	m_testpicture(new Mat(240, 320, CV_8UC3))
{
	string filepath = "resources/testfiles/" + filename + ".png";
	Mat img = imread(filepath);
	if(!img.data)
		cout << "could not open file";
	else
		*m_testpicture = img;
}

cv::Mat CameraMock::getFrame()
{
	++m_callsToGetFrame;
	return *m_testpicture;
}

bool CameraMock::isValid() const
{
	return true;
}

unsigned int CameraMock::getCallsToGetFrame() const
{
	return m_callsToGetFrame;
}
