#include "cameraobjecttest.h"
#include "layer/dataanalysis/cameraobject.h"

using namespace std;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


void CameraObjectTest::getColorType_ColorTypeYellowGoal()
{
	CameraObject cameraobject(FieldObjectColorYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorYellow, cameraobject.getColorType());
}

void CameraObjectTest::getPosition_positionIs0And0()
{
	CameraObject cameraobject(FieldObjectColorYellow, Point(0,0));

	CPPUNIT_ASSERT_EQUAL(Point(0,0), cameraobject.getPosition());
}
