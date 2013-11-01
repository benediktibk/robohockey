#include "layer/dataanalysis/lidarobjectdistancecomparatortest.h"
#include "layer/dataanalysis/lidarobjectdistancecomparator.h"
#include "layer/dataanalysis/lidarobject.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

void LidarObjectDistanceComparatorTest::operator_firstOneCloser_true()
{
	LidarObjectDistanceComparator comparator(Point(1, 2));
	LidarObject objectOne(Point(3, 3), 1);
	LidarObject objectTwo(Point(10, 10), 2);

	CPPUNIT_ASSERT(comparator(objectOne, objectTwo));
}

void LidarObjectDistanceComparatorTest::operator_secondOneCloser_false()
{
	LidarObjectDistanceComparator comparator(Point(1, 2));
	LidarObject objectOne(Point(10, 10), 2);
	LidarObject objectTwo(Point(3, 3), 1);

	CPPUNIT_ASSERT(!comparator(objectOne, objectTwo));
}

void LidarObjectDistanceComparatorTest::operator_firstOneThrougBigDiameterCloser_true()
{
	LidarObjectDistanceComparator comparator(Point(1, 2));
	LidarObject objectOne(Point(3, 4), 1.5);
	LidarObject objectTwo(Point(3, 0), 0.5);

	CPPUNIT_ASSERT(comparator(objectOne, objectTwo));
}

void LidarObjectDistanceComparatorTest::operator_secondOneThrougBidDiameterCloser_false()
{
	LidarObjectDistanceComparator comparator(Point(1, 2));
	LidarObject objectOne(Point(3, 0), 0.5);
	LidarObject objectTwo(Point(3, 4), 1.5);

	CPPUNIT_ASSERT(!comparator(objectOne, objectTwo));
}
