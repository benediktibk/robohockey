#include <cv.h>
#include <sstream>
#include <iostream>
#include "layer/hardware/cameraimpl.h"

//Including this files manually as <highgui.h> is missing on robot.
#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;
using namespace RoboHockey;

int main(int /*argc*/, char **/*argv*/)
{
	cout << "##\n## Take a picture to current dir with 'p'.\n## Exit with 'q'\n##"<< endl;

	Layer::Hardware::Camera *camera = new Layer::Hardware::CameraImpl();
	Mat frame;
	int pictureNumber = 0;
	stringstream pictureName;

	namedWindow( "Video", CV_WINDOW_AUTOSIZE );

		char k;
		while(true)
		{
			frame = camera->getFrame();
			imshow( "Video", frame );

			k = cvWaitKey(25);
			if (k == 'q') break;

			if (k == 'p')
			{
				pictureName << "image" << setfill('0') << setw(3) << pictureNumber << ".png";
				imwrite(pictureName.str(), frame);
				pictureName.str("");
				pictureNumber++;
			}
		}

	return 0;
}

