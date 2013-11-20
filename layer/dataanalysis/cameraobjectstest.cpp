#include "cameraobjectstest.h"
#include "layer/dataanalysis/cameraobjects.h"

using namespace std;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;


void CameraObjectsTest::getObjectCount_add1Object_objectCountIs1()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, Point(0,0));

	objects.addObject(objectOne);

	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.getObjectCount());
}

void CameraObjectsTest::getColorType_add2Objects_secondObjectIsYellow()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, Point(0,0));
	CameraObject objectTwo(ColorTypeYellow, Point(0,1));

	objects.addObject(objectOne);
	objects.addObject(objectTwo);

	CPPUNIT_ASSERT_EQUAL(ColorTypeYellow, objects.back().getColorType());
}

void CameraObjectsTest::getCameraObjectAtPosition_4ObjectsAndPositionIs3And3_ObjectAtPositionIsObject3()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, Point(0,0));
	CameraObject objectTwo(ColorTypeYellow, Point(0,1));
	CameraObject objectThree(ColorTypeBlue, Point(3.03,3.04));
	CameraObject objectFour(ColorTypeGreen, Point(3.03,3.5));

	objects.addObject(objectOne);
	objects.addObject(objectTwo);
	objects.addObject(objectThree);
	objects.addObject(objectFour);

	CPPUNIT_ASSERT_EQUAL(objectThree.getColorType(), objects.getCameraObjectAtPosition(Point(3,3)).getColorType());
}

void CameraObjectsTest::getCameraObjectAtPosition_3ObjectsAndPositionIs3And3AndNoObjectInRange_NextObjectAtPositionIsObject2()
{
	CameraObjects objects;
	CameraObject objectOne(ColorTypeUnknown, Point(0,0));
	CameraObject objectTwo(ColorTypeYellow, Point(0,1));
	CameraObject objectThree(ColorTypeBlue, Point(3.5,3.5));

	objects.addObject(objectOne);
	objects.addObject(objectTwo);
	objects.addObject(objectThree);

	CPPUNIT_ASSERT_EQUAL(objectThree.getColorType(), objects.getCameraObjectAtPosition(Point(3,3)).getColorType());
}
