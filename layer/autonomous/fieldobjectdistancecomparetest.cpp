#include "layer/autonomous/fieldobjectdistancecomparetest.h"
#include "layer/autonomous/fieldobjectdistancecompare.h"
#include "layer/autonomous/fieldobject.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void FieldObjectDistanceCompareTest::compare_firstOneCloserThanSecondOneBecauseOfPosition_true()
{
	FieldObject one(Circle(Point(3, 4), 0.1), FieldColorBlue, 2);
	FieldObject two(Circle(Point(-3, 4), 0.1), FieldColorBlue, 2);
	FieldObjectDistanceCompare compare(Point(2, 4));

	CPPUNIT_ASSERT(compare(one, two));
}

void FieldObjectDistanceCompareTest::compare_seoncdOneCloserThanFirstOneBecauseOfPosition_false()
{
	FieldObject one(Circle(Point(3, 4), 0.1), FieldColorBlue, 2);
	FieldObject two(Circle(Point(-3, 4), 0.1), FieldColorBlue, 2);
	FieldObjectDistanceCompare compare(Point(-3, 3));

	CPPUNIT_ASSERT(!compare(one, two));
}

void FieldObjectDistanceCompareTest::compare_firstOneCloserThanSecondOneBecauseOfBigDiameter_true()
{
	FieldObject one(Circle(Point(3, 4), 3), FieldColorBlue, 2);
	FieldObject two(Circle(Point(-2, 4), 0.1), FieldColorBlue, 2);
	FieldObjectDistanceCompare compare(Point(0, 0));

	CPPUNIT_ASSERT(compare(one, two));
}

void FieldObjectDistanceCompareTest::compare_seoncdOneCloserThanFirstOneBecauseOfBigDiameter_false()
{
	FieldObject one(Circle(Point(2, 4), 0.1), FieldColorBlue, 2);
	FieldObject two(Circle(Point(-3, 4), 3), FieldColorBlue, 2);
	FieldObjectDistanceCompare compare(Point(0, 0));

	CPPUNIT_ASSERT(!compare(one, two));
}
