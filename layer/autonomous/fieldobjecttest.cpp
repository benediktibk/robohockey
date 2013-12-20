#include "layer/autonomous/fieldobjecttest.h"
#include "layer/autonomous/fieldobject.h"
#include "common/compare.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

void FieldObjectTest::constructor_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen);

	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(circle, object.getCircle()));
}

void FieldObjectTest::constructor_validColor_getCircleReturnsSameColor()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen);

	CPPUNIT_ASSERT_EQUAL(FieldColorGreen, object.getColor());
}

void FieldObjectTest::constructor_validArguments_seenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getSeen());
}

void FieldObjectTest::constructor_validArguments_notSeenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getNotSeen());
}

void FieldObjectTest::constructor_validArguments_shouldBeSeenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getShouldBeSeen());
}

void FieldObjectTest::setColor_blueColor_IsBlueColor()
{
	Circle circle(Point(2,3), 5);

	FieldObject object(circle, FieldColorUnknown);

	object.setColor(FieldColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, object.getColor());
}

void FieldObjectTest::setCircle_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen);

	Circle newCircle(Point(2, 7), 5);
	object.setCircle(newCircle);


	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(newCircle, object.getCircle()));
}

void FieldObjectTest::seen_empty_seenIs1()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getSeen());
}

void FieldObjectTest::seen_threeTimesCalled_seenIs3()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.seen();
	object.seen();
	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, object.getSeen());
}

void FieldObjectTest::seen_previouslyNotSeenCalled_notSeenIs0()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.notSeen();
	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getNotSeen());
}

void FieldObjectTest::notSeen_empty_notSeenIs1()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getNotSeen());
}

void FieldObjectTest::notSeen_twiceCalled_notSeenIs2()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.notSeen();
	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, object.getNotSeen());
}

void FieldObjectTest::notSeen_previouslySeenCalled_seenIs0()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.seen();
	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getSeen());
}

void FieldObjectTest::shouldBeSeen_twiceCalled_shouldBeSeenIs2()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen);

	object.shouldBeSeen();
	object.shouldBeSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, object.getShouldBeSeen());
}
