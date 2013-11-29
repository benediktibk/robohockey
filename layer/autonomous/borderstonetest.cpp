#include "layer/autonomous/borderstonetest.h"
#include "layer/autonomous/borderstone.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RoboHockey::Layer::Autonomous::BorderStoneTest::getNumberOfChildrenRecursive_noChildren_is0()
{
	BorderStoneDistances distances;
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position);

	vector<Point*> possibleChildren;

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL(0, borderstone.getNumberOfChildrenRecursive());
}

void BorderStoneTest::getNumberOfChildrenRecursive_twoChildren_is2()
{
	BorderStoneDistances distances;
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position);

	vector<Point*> possibleChildren;
	possibleChildren.push_back(new Point(0,distances.getStandardFieldDistance(BorderStoneFieldDistanceA)));
	possibleChildren.push_back(new Point(0,-1.0* distances.getStandardFieldDistance(BorderStoneFieldDistanceB)));

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL(2, borderstone.getNumberOfChildrenRecursive());
}

void BorderStoneTest::getDistanceToFather_root_isRoot()
{
	BorderStoneDistances distances;
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position);

	CPPUNIT_ASSERT_EQUAL(BorderStoneFieldDistanceRoot, borderstone.getDistanceToFather());
}

void BorderStoneTest::getDistanceToFather_distanceB_isDistanceB()
{
	BorderStoneDistances distances;
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceB, distances, position);

	CPPUNIT_ASSERT_EQUAL(BorderStoneFieldDistanceB, borderstone.getDistanceToFather());
}
