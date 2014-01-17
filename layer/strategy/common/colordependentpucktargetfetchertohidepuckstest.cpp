#include "layer/strategy/common/colordependentpucktargetfetchertohidepuckstest.h"
#include "layer/strategy/common/colordependentpucktargetfetchertohidepucks.h"
#include "layer/autonomous/fieldmock.h"
#include "common/fieldcolor.h"
#include <vector>

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;
using namespace std;

void ColorDependentPuckTargetFetcherToHidePucksTest::getColorOfTargetPucks_ownColorIsYellow_resultIsBlue()
{
	FieldMock field;
	field.setTrueTeamColor(FieldColorYellow);
	ColorDependentPuckTargetFetcherToHidePucks puckTargetFetcher(field);

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, puckTargetFetcher.getColorOfTargetPucks());
}

void ColorDependentPuckTargetFetcherToHidePucksTest::getNumberOfKnownPucksNotInTarget_oneKnownPuck_resultIs1()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown, 2));
	field.setFieldObjects(objects);
	ColorDependentPuckTargetFetcherToHidePucks puckTargetFetcher(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, puckTargetFetcher.getNumberOfKnownPucksNotInTarget());
}

void ColorDependentPuckTargetFetcherToHidePucksTest::getNumberOfKnownPucksNotInTarget_threePucksOnePuckHidden_resultIs2()
{
	FieldMock field;
	vector<FieldObject> objects;
	objects.push_back(FieldObject(Circle(Point(1,1), 0.2), FieldColorUnknown, 2));
	objects.push_back(FieldObject(Circle(Point(1,2), 0.2), FieldColorUnknown, 2));
	objects.push_back(FieldObject(Circle(Point(2,1), 0.2), FieldColorUnknown, 2));
	field.setFieldObjects(objects);
	field.setEnemyHiddenPucks(1);
	ColorDependentPuckTargetFetcherToHidePucks puckTargetFetcher(field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, puckTargetFetcher.getNumberOfKnownPucksNotInTarget());
}

void ColorDependentPuckTargetFetcherToHidePucksTest::isCantReachedTargetLimitReached_limitNotReached_false()
{
	FieldMock field;
	ColorDependentPuckTargetFetcherToHidePucks puckTargetFetcher(field);

	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();

	CPPUNIT_ASSERT(!puckTargetFetcher.isCantReachTargetLimitReached());
}

void ColorDependentPuckTargetFetcherToHidePucksTest::isCantReachedTargetLimitReached_limitReached_true()
{
	FieldMock field;
	ColorDependentPuckTargetFetcherToHidePucks puckTargetFetcher(field);

	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();
	puckTargetFetcher.increaseCantReachTargetCounter();

	CPPUNIT_ASSERT(puckTargetFetcher.isCantReachTargetLimitReached());
}
