#include <cv.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "layer/hardware/cameraimpl.h"

using namespace std;
using namespace cv;
using namespace RoboHockey::Layer::Hardware;

bool findOurChessboard(Mat &frame, vector<Point2f> &pointBuf);
bool compareCurrentPointsWithDefault(vector<Point2f> &resultPoints, double tolerance);
void loadDefaultChessboardPoints();

Size g_boardSize(5,3);
vector<Point2f> defaultChessboardPoints;
double g_tolerance = 2.0;


int main()
{

	cout << "##\n## Take a picture to current dir with 'p'.\n## Exit with 'q'\n##"<< endl;

	Camera *camera = new CameraImpl(0);

	if (!camera->isValid())
	{
		cout << "\n\n###\n### Could not open camera!\n###" << endl;
		return 1;
	}

	loadDefaultChessboardPoints();

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
			//cout << chessBoardPoints.front() << chessBoardPoints.back() << endl;

			if (compareCurrentPointsWithDefault(chessBoardPoints, g_tolerance))
				cout << "GOOD CAMERA POSITION!" << endl;
			else
				cout << "Camera Position not correct" << endl;


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
	found = findChessboardCorners(frame, g_boardSize, resultPoints,
								  CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

	if (found)
	{
		Mat viewGray;
		cvtColor(frame, viewGray, CV_BGR2GRAY);
		cornerSubPix( viewGray, resultPoints, Size(11,11),Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
		drawChessboardCorners( frame, g_boardSize, Mat(resultPoints), found );
	}

	return found;
}

void loadDefaultChessboardPoints()
{
	defaultChessboardPoints.push_back(Point2f(115,184));
	defaultChessboardPoints.push_back(Point2f(133,184));
	defaultChessboardPoints.push_back(Point2f(152,184));
	defaultChessboardPoints.push_back(Point2f(171,184));
	defaultChessboardPoints.push_back(Point2f(190,184));

	defaultChessboardPoints.push_back(Point2f(112,201));
	defaultChessboardPoints.push_back(Point2f(132,201));
	defaultChessboardPoints.push_back(Point2f(152,201));
	defaultChessboardPoints.push_back(Point2f(172,201));
	defaultChessboardPoints.push_back(Point2f(192,201));

	defaultChessboardPoints.push_back(Point2f(110,219));
	defaultChessboardPoints.push_back(Point2f(131,219));
	defaultChessboardPoints.push_back(Point2f(152,219));
	defaultChessboardPoints.push_back(Point2f(173,219));
	defaultChessboardPoints.push_back(Point2f(195,219));
}

bool compareCurrentPointsWithDefault(vector<Point2f> &resultPoints, double tolerance)
{

	if (! resultPoints.size() == defaultChessboardPoints.size())
	{
		cout << "Number of Points does not equal preset" << endl;
		return false;
	}

	bool positionCorrect = true;

	for(unsigned int i =0; i < defaultChessboardPoints.size(); i++)
	{
		if (((resultPoints[i] - defaultChessboardPoints[i]).x > tolerance) || ((resultPoints[i] - defaultChessboardPoints[i]).y > tolerance))
		{
			positionCorrect = false;
			break;
		}
	}

	if (!positionCorrect)
	{
		positionCorrect = true;
		for(unsigned int i =0; i < defaultChessboardPoints.size(); i++)
		{
			if (((resultPoints[defaultChessboardPoints.size() - (i+1)] - defaultChessboardPoints[i]).x > tolerance) || ((resultPoints[defaultChessboardPoints.size() - (i+1)] - defaultChessboardPoints[i]).y > tolerance))
			{
				positionCorrect = false;
				break;
			}
		}
	}

	return positionCorrect;
}
