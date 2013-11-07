#include <cv.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "layer/hardware/cameraimpl.h"

using namespace std;
using namespace cv;
using namespace RoboHockey::Layer::Hardware;

bool findOurChessboard(Mat &frame, vector<Point2f> &pointBuf);
void initializeAndCalibrateCamera();
Size g_boardSize(10,7);


int main()
{

	cout << "##\n## Take a picture to current dir with 'p'.\n## Exit with 'q'\n##"<< endl;

	Camera *camera = new CameraImpl(0);

	if (!camera->isValid())
	{
		cout << "\n\n###\n### Could not open camera!\n###" << endl;
		return 1;
	}

	Mat frame;
	int pictureNumber = 0;
	stringstream pictureName;
	vector<Point2f> chessBoardPoints;

	namedWindow( "Video", CV_WINDOW_AUTOSIZE );

	char key;
	while(true)
	{
		chessBoardPoints.clear();

		frame = camera->getFrame();

		if (findOurChessboard(frame, chessBoardPoints))
		{
			fstream fileChessboardPoints("chessboardpoints.txt", ios_base::out | ios_base::trunc);
			cout << "Chessboard found!!! Points: " << chessBoardPoints.size() << endl;
			cout << chessBoardPoints.front() << chessBoardPoints.back() << endl;

			for(std::vector<Point2f>::iterator i = chessBoardPoints.begin(); i != chessBoardPoints.end(); ++i)
			{
				fileChessboardPoints << *i << endl;
			}
		}


		imshow( "Video", frame );


		key = cvWaitKey(25);
		if (key == 'q') break;

		if (key == 'p')
		{
			pictureName << "image" << pictureNumber << ".png";
			imwrite(pictureName.str(), frame);
			pictureName.str("");
			pictureNumber++;
		}
	}


	return 0;
}

bool findOurChessboard(Mat &frame, vector<Point2f> &resultPoints)
{
	bool found;
	found = findChessboardCorners(frame, g_boardSize, resultPoints,CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

	if (found)
	{
		Mat viewGray;
		cvtColor(frame, viewGray, CV_BGR2GRAY);
		cornerSubPix( viewGray, resultPoints, Size(11,11),Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
		drawChessboardCorners( frame, g_boardSize, Mat(resultPoints), found );
	}

	return found;
}

void initializeAndCalibrateCamera()
{

}
