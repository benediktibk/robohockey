#include "layer/hardware/cameramock.h"
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;
using namespace std;
using namespace cv;

CameraMock::CameraMock() :
	m_testpicture(new Mat(240, 320, CV_8UC3))
{
	setBlackPicture();
}

CameraMock::CameraMock(const string &filename) :
	m_testpicture(new Mat(240, 320, CV_8UC3))
{
	setBlackPicture();
	string filepath = "resources/testfiles/" + filename + ".png";
	readDataFromFile(filepath);
}

CameraMock::~CameraMock()
{
	delete m_testpicture;
	m_testpicture = 0;
}

Mat CameraMock::getFrame() const
{
	return *m_testpicture;
}

bool CameraMock::isValid() const
{
	return true;
}

void CameraMock::writeDataToFile(const string &) const
{ }

void CameraMock::readDataFromFile(const string &fileName)
{
	assert(boost::filesystem::exists(fileName));
	Mat img = imread(fileName);
	assert(img.data);
	*m_testpicture = img;
}

void CameraMock::setBlackPicture()
{
	m_testpicture->setTo(Scalar(0, 0, 0));
}