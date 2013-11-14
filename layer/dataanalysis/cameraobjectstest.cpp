#include "cameraobjectstest.h"
#include "layer/dataanalysis/cameraobjects.h"

using namespace std;
using namespace RoboHockey::Layer::DataAnalysis;


void CameraObjectsTest::getObjectCount_add1Object_objectCountIs1()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, cv::Rect(0,0,1,1));

	objects.addObject(objectOne);

	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.getObjectCount());
}

void CameraObjectsTest::getAllCameraObjects_add2Objects_secondObjectIsYellow()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, cv::Rect(0,0,1,1));
	CameraObject objectTwo(ColorTypeYellow, cv::Rect(0,0,1,1));

	objects.addObject(objectOne);
	objects.addObject(objectTwo);

	CPPUNIT_ASSERT_EQUAL(ColorTypeYellow, objects.getAllCameraObjects().back().getColorType());
}
