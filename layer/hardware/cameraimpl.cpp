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

	if (! m_capture->isOpened())
	{
		cout << "\n\n###\n### Could not open camera!\n###" << endl;
		//assert(false);
	}
}

CameraImpl::~CameraImpl()
{
	delete m_capture;
	m_capture = 0;
}

Mat CameraImpl::getFrame()
{
	Mat frame;
	m_capture->operator >> (frame);

	return frame;
}
