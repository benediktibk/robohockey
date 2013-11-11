#include "cameraobjecttest.h"
#include "layer/dataanalysis/cameraobject.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;


void CameraObjectTest::getColorType_ColorTypeYellowGoal()
{
	CameraObject cameraobject(ColorTypeYellowGoal, cv::Rect(0,0,1,1));

	CPPUNIT_ASSERT_EQUAL(ColorTypeYellowGoal, cameraobject.getColorType());
}

void CameraObjectTest::getImagePositionArea_RectArea100()
{
	CameraObject cameraobject(ColorTypeYellowGoal, cv::Rect(0,0,10,10));

	CPPUNIT_ASSERT_EQUAL(100, cameraobject.getImagePosition().area());
}
