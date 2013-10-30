#include "layer/hardware/cameraimpl.h"
#include <libplayerc++/playerc++.h>
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;
using namespace cv;
using namespace PlayerCc;

CameraImpl::CameraImpl(int device)
{
	m_capture = new VideoCapture;
	m_capture->open(device);

	if (! m_capture->isOpened())
	{
		assert(false);
	}
}

CameraImpl::~CameraImpl()
{
	delete m_capture;
}

Mat CameraImpl::getFrame()
{
	Mat frame;
	m_capture->operator >> (frame);

	return frame;
}
