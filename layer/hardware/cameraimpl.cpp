#include "layer/hardware/cameraimpl.h"
#include <libplayerc++/playerc++.h>
#include <assert.h>
#include <iostream>

using namespace RoboHockey::Layer::Hardware;
using namespace cv;
using namespace PlayerCc;
using namespace std;

CameraImpl::CameraImpl(int device)
{
	m_capture = new VideoCapture;
	m_capture->open(device);
}

CameraImpl::~CameraImpl()
{
	delete m_capture;
	m_capture = 0;
}

Mat CameraImpl::getFrame() const
{
	assert(isValid());

	Mat frame;
	m_capture->operator >> (frame);

	return frame;
}

bool CameraImpl::isValid() const
{
	return m_capture->isOpened();
}

void CameraImpl::writeDataToFile(const string &fileName) const
{
	Mat frame = getFrame();
	imwrite(fileName, frame);
}

CameraImpl::CameraImpl(const CameraImpl &)
{ }

void CameraImpl::operator=(const CameraImpl &)
{ }
