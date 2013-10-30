#include <cv.h>
#include <highgui.h>
#include <iostream>
//#include "layer/hardware/robotimpl.h"
#include "layer/hardware/cameraimpl.h"

using namespace std;
using namespace cv;
using namespace RoboHockey;

int main(int /*argc*/, char **/*argv*/)
{
	Layer::Hardware::Camera *camera = new Layer::Hardware::CameraImpl();

	Mat frame;

	namedWindow( "Video", CV_WINDOW_AUTOSIZE );

		char k;
		while(true)
		{
			frame = camera->getFrame();
			imshow( "Video", frame );

			k = cvWaitKey(25);
			if (k == 'q') break;
		}

	return 0;
}

