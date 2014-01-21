#include "cameraobjecttest.h"
#include "layer/dataanalysis/cameraobject.h"

using namespace std;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void CameraObjectTest::getColorType_ColorTypeYellowGoal()
{
	CameraObject cameraobject(FieldColorYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, cameraobject.getColor());
}

void CameraObjectTest::getPosition_positionIs0And0()
{
	CameraObject cameraobject(FieldColorYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Point(0,0), cameraobject.getPosition());
}
