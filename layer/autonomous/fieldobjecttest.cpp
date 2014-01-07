#include "layer/autonomous/fieldobjecttest.h"
#include "layer/autonomous/fieldobject.h"
#include "common/compare.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

void FieldObjectTest::constructor_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen, 2);

	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(circle, object.getCircle()));
}

void FieldObjectTest::constructor_validColor_getCircleReturnsSameColor()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen, 2);

	CPPUNIT_ASSERT_EQUAL(FieldColorGreen, object.getColor());
}

void FieldObjectTest::constructor_validArguments_seenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getSeen());
}

void FieldObjectTest::constructor_validArguments_notSeenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getNotSeen());
}

void FieldObjectTest::constructor_validArguments_shouldBeSeenIs0()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getShouldBeSeen());
}

void FieldObjectTest::constructor_seenIs1_seenIs1()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2, 1, 3, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getSeen());
}

void FieldObjectTest::constructor_notSeenIs2_notSeenIs2()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2, 1, 3, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, object.getNotSeen());
}

void FieldObjectTest::constructor_shouldBeSeenIs3_shouldBeSeenIs3()
{
	FieldObject object(Circle(Point(1, 2), 3), FieldColorUnknown, 2, 1, 3, 2);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, object.getShouldBeSeen());
}

void FieldObjectTest::setColor_blueColor_IsBlueColor()
{
	Circle circle(Point(2,3), 5);

	FieldObject object(circle, FieldColorUnknown, 2);

	object.setColor(FieldColorBlue);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, object.getColor());
}

void FieldObjectTest::setCircle_validCircle_getCircleReturnsSameCircle()
{
	Circle circle(Point(4, 3), 2);

	FieldObject object(circle, FieldColorGreen, 2);

	Circle newCircle(Point(2, 7), 5);
	object.setCircle(newCircle);


	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(newCircle, object.getCircle()));
}

void FieldObjectTest::seen_empty_seenIs1()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getSeen());
}

void FieldObjectTest::seen_threeTimesCalled_seenIs3()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.seen();
	object.seen();
	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, object.getSeen());
}

void FieldObjectTest::seen_previouslyNotSeenCalled_notSeenIs0()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.notSeen();
	object.seen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getNotSeen());
}

void FieldObjectTest::notSeen_empty_notSeenIs1()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getNotSeen());
}

void FieldObjectTest::notSeen_twiceCalled_notSeenIs2()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.notSeen();
	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, object.getNotSeen());
}

void FieldObjectTest::notSeen_previouslySeenCalled_seenIs1()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.seen();
	object.notSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getSeen());
}

void FieldObjectTest::shouldBeSeen_twiceCalled_shouldBeSeenIs2()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.shouldBeSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, object.getShouldBeSeen());
}

void FieldObjectTest::cantBeSeen_twiceNotSeen_notSeenIs0()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.seen();
	object.shouldBeSeen();
	object.notSeen();
	object.shouldBeSeen();
	object.notSeen();
	object.cantBeSeen();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, object.getNotSeen());
	CPPUNIT_ASSERT_EQUAL((unsigned int)3, object.getShouldBeSeen());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, object.getSeen());
}

void FieldObjectTest::isDefinitelyExisting_shouldBeSeenOnlyOnceAndSeen_false()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.seen();

	CPPUNIT_ASSERT(!object.isDefinitelyExisting());
}

void FieldObjectTest::isDefinitelyExisting_shouldBeSeenAndSeenVeryOften_true()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.seen();
	object.shouldBeSeen();
	object.seen();

	CPPUNIT_ASSERT(object.isDefinitelyExisting());
}

void FieldObjectTest::isDefinitelyNotExisting_notSeenOnce_false()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.notSeen();

	CPPUNIT_ASSERT(!object.isDefinitelyNotExisting());
}

void FieldObjectTest::isDefinitelyNotExisting_notSeenOnceAndThenSeenAgain_false()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.notSeen();

	CPPUNIT_ASSERT(!object.isDefinitelyNotExisting());
	CPPUNIT_ASSERT(!object.isDefinitelyExisting());
}

void FieldObjectTest::isDefinitelyNotExisting_notSeenVeryOften_true()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 2);

	object.shouldBeSeen();
	object.notSeen();
	object.shouldBeSeen();
	object.notSeen();

	CPPUNIT_ASSERT(object.isDefinitelyNotExisting());
}

void FieldObjectTest::isMaybeExisting_seenOnceAndTresholdIs4_false()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 4);

	object.shouldBeSeen();
	object.seen();
	object.shouldBeSeen();

	CPPUNIT_ASSERT(!object.isMaybeExisting());
}

void FieldObjectTest::isMaybeExisting_seenTwiceAndTresholdIs4_true()
{
	Circle circle(Point(4, 3), 2);
	FieldObject object(circle, FieldColorGreen, 4);

	object.shouldBeSeen();
	object.seen();
	object.shouldBeSeen();
	object.seen();

	CPPUNIT_ASSERT(object.isMaybeExisting());
}

void FieldObjectTest::isHardObstacle_verySmallAndGreen_true()
{
	Circle circle(Point(4, 3), 0.02);
	FieldObject object(circle, FieldColorGreen, 4);

	CPPUNIT_ASSERT(object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_verySmallAndBlue_false()
{
	Circle circle(Point(4, 3), 0.02);
	FieldObject object(circle, FieldColorBlue, 4);

	CPPUNIT_ASSERT(!object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_verySmallAndYellow_false()
{
	Circle circle(Point(4, 3), 0.02);
	FieldObject object(circle, FieldColorYellow, 4);

	CPPUNIT_ASSERT(!object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_verySmallAndUnknownColor_false()
{
	Circle circle(Point(4, 3), 0.02);
	FieldObject object(circle, FieldColorUnknown, 4);

	CPPUNIT_ASSERT(!object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_veryBigAndGreen_true()
{
	Circle circle(Point(4, 3), 0.135);
	FieldObject object(circle, FieldColorGreen, 4);

	CPPUNIT_ASSERT(object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_veryBigAndBlue_true()
{
	Circle circle(Point(4, 3), 0.135);
	FieldObject object(circle, FieldColorBlue, 4);

	CPPUNIT_ASSERT(object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_veryBigAndYellow_true()
{
	Circle circle(Point(4, 3), 0.135);
	FieldObject object(circle, FieldColorYellow, 4);

	CPPUNIT_ASSERT(object.isHardObstacle());
}

void FieldObjectTest::isHardObstacle_veryBigAndUnkownColor_true()
{
	Circle circle(Point(4, 3), 0.135);
	FieldObject object(circle, FieldColorUnknown, 4);

	CPPUNIT_ASSERT(object.isHardObstacle());
}

void FieldObjectTest::getObstacle_green_boundaryPost()
{
	Circle circle(Point(4, 3), 0.03);
	FieldObject object(circle, FieldColorGreen, 4);

	Circle obstacle = object.getObstacle();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(4, 3), 0.06), obstacle));
}

void FieldObjectTest::getObstacle_blue_bluePuck()
{
	Circle circle(Point(4, 3), 0.03);
	FieldObject object(circle, FieldColorBlue, 4);

	Circle obstacle = object.getObstacle();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(4, 3), 0.12), obstacle));
}

void FieldObjectTest::getObstacle_yellow_yellowPuck()
{
	Circle circle(Point(1, 3), 0.03);
	FieldObject object(circle, FieldColorYellow, 4);

	Circle obstacle = object.getObstacle();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 3), 0.12), obstacle));
}

void FieldObjectTest::getObstacle_smallAndUnknownColor_puckSize()
{
	Circle circle(Point(1, 2), 0.03);
	FieldObject object(circle, FieldColorUnknown, 4);

	Circle obstacle = object.getObstacle();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 2), 0.12), obstacle));
}

void FieldObjectTest::getObstacle_big_enemyRobot()
{
	Circle circle(Point(4, 3), 0.135);
	FieldObject object(circle, FieldColorBlue, 4);

	Circle obstacle = object.getObstacle();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(4, 3), 0.8), obstacle));
}
