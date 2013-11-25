#include "layer/autonomous/fieldobjecttest.h"
#include "layer/autonomous/fieldobject.h"
#include "common/compare.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

void FieldObjectTest::constructor_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldObjectColorGreen);

	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(circle, object.getCircle()));
}

void FieldObjectTest::constructor_validColor_getCircleReturnsSameColor()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldObjectColorGreen);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorGreen, object.getColor());
}

void FieldObjectTest::setColor_blueColor_IsBlueColor()
{
	Circle circle(Point(2,3), 5);

	FieldObject object(circle, FieldObjectColorUnknown);

	object.setColor(FieldObjectColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorBlue, object.getColor());
}

void FieldObjectTest::setCircle_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldObjectColorGreen);

	Circle newCircle(Point(2, 7), 5);
	object.setCircle(newCircle);


	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(newCircle, object.getCircle()));
}
