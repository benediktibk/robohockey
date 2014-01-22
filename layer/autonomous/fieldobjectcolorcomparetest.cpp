#include "layer/autonomous/fieldobjectcolorcomparetest.h"
#include "layer/autonomous/fieldobjectcolorcompare.h"
#include "layer/autonomous/fieldobject.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void FieldObjectColorCompareTest::evaluate_yellowAndUnknown_true()
{
	FieldObject one(Circle(), FieldColorYellow, 1);
	FieldObject two(Circle(), FieldColorUnknown, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(compare(one, two));
}

void FieldObjectColorCompareTest::evaluate_greenAndUnknown_true()
{
	FieldObject one(Circle(), FieldColorGreen, 1);
	FieldObject two(Circle(), FieldColorUnknown, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(compare(one, two));
}

void FieldObjectColorCompareTest::evaluate_blueAndUnknown_true()
{
	FieldObject one(Circle(), FieldColorBlue, 1);
	FieldObject two(Circle(), FieldColorUnknown, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(compare(one, two));
}

void FieldObjectColorCompareTest::evaluate_unknownAndYellow_false()
{
	FieldObject one(Circle(), FieldColorUnknown, 1);
	FieldObject two(Circle(), FieldColorYellow, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(!compare(one, two));
}

void FieldObjectColorCompareTest::evaluate_unknownAndBlue_false()
{
	FieldObject one(Circle(), FieldColorUnknown, 1);
	FieldObject two(Circle(), FieldColorBlue, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(!compare(one, two));
}

void FieldObjectColorCompareTest::evaluate_unknownAndGreen_false()
{
	FieldObject one(Circle(), FieldColorUnknown, 1);
	FieldObject two(Circle(), FieldColorGreen, 1);
	FieldObjectColorCompare compare;

	CPPUNIT_ASSERT(!compare(one, two));
}
