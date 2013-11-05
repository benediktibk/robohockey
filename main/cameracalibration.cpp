#include <cv.h>
#include <sstream>
#include <iostream>
#include "layer/hardware/cameraimpl.h"

// Including these files manually as <highgui.h> is missing on robot.
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

	Layer::Hardware::Camera *camera = new Layer::Hardware::CameraImpl(0);

	if (!camera->isValid())
	{
		cout << "\n\n###\n### Could not open camera!\n###" << endl;
		return 1;
	}

	Mat frame;

	int pictureNumber = 0;
	stringstream pictureName;
	namedWindow( "Video", CV_WINDOW_AUTOSIZE );
	char key;

	while(true)
	{
		frame = camera->getFrame();
		imshow( "Video", frame );

		key = cvWaitKey(25);
		if (key == 'q') break;

		if (key == 'p')
		{
			pictureName << "image" << setfill('0') << setw(3) << pictureNumber << ".png";
			imwrite(pictureName.str(), frame);
			pictureName.str("");
			pictureNumber++;
		}
	}

	return 0;
}

void calibrateOnOurChessboard(Mat &frame, bool &found)
{
	Size chessboardSize(6,9);
	vector<Point2f> pointBuf;

	found = findChessboardCorners(frame, chessboardSize, pointBuf, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

	if (found)
	{
		Mat viewGray;
		cvtColor(frame, viewGray, COLOR_BGR2GRAY);
		cornerSubPix( viewGray, pointBuf, Size(11,11),Size(-1,-1), TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 30, 0.1 ));
	}

}

void calibrateOurCamera()
{

}
