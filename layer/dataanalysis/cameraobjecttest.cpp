#include "cameraobjecttest.h"
#include "layer/dataanalysis/cameraobject.h"

using namespace std;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


void CameraObjectTest::getColorType_ColorTypeYellowGoal()
{
	CameraObject cameraobject(ColorTypeYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(ColorTypeYellow, cameraobject.getColorType());
}

void CameraObjectTest::getImagePosition_positionIs0And0()
{
	CameraObject cameraobject(ColorTypeYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Point(0,0), cameraobject.getPosition());
}
