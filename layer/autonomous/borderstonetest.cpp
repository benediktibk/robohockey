#include "layer/autonomous/borderstonetest.h"
#include "layer/autonomous/borderstone.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RoboHockey::Layer::Autonomous::BorderStoneTest::getNumberOfChildrenRecursive_noChildren_is0()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	vector<Point*> possibleChildren;

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL((unsigned int) 0, borderstone.getNumberOfChildrenRecursive());
}

void BorderStoneTest::getNumberOfChildrenRecursive_twoChildren_is2()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	vector<Point*> possibleChildren;
	possibleChildren.push_back(new Point(0,distances.getStandardFieldDistance(BorderStoneFieldDistanceA)));
	possibleChildren.push_back(new Point(0,-1.0* distances.getStandardFieldDistance(BorderStoneFieldDistanceB)));

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL((unsigned int) 2, borderstone.getNumberOfChildrenRecursive());
}

void BorderStoneTest::getDistanceToFather_root_isRoot()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	CPPUNIT_ASSERT_EQUAL(BorderStoneFieldDistanceRoot, borderstone.getDistanceToFather());
}

void BorderStoneTest::getDistanceToFather_distanceB_isDistanceB()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceB, distances, position, 0.05);

	CPPUNIT_ASSERT_EQUAL(BorderStoneFieldDistanceB, borderstone.getDistanceToFather());
}

void BorderStoneTest::getAllChildren_noValidChildren_isEmpty()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	vector<Point*> possibleChildren;
	possibleChildren.push_back(new Point(0,1.53));
	possibleChildren.push_back(new Point(0.76,-2.34));

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL((size_t)0, borderstone.getAllChildren().size());
}

void BorderStoneTest::getAllChildren_2validChildren_has2Entries()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	vector<Point*> possibleChildren;
	possibleChildren.push_back(new Point(0,distances.getStandardFieldDistance(BorderStoneFieldDistanceA)));
	possibleChildren.push_back(new Point(0,-1.0* distances.getStandardFieldDistance(BorderStoneFieldDistanceB)));

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT_EQUAL((size_t)2, borderstone.getAllChildren().size());
}

void BorderStoneTest::getAllChildren_2validChildren_correctChildren()
{
	BorderStoneDistances distances(0.07);
	Point father;
	Point position;
	BorderStone borderstone(father, BorderStoneFieldDistanceRoot, distances, position, 0.05);

	vector<Point*> possibleChildren;
	possibleChildren.push_back(new Point(0,distances.getStandardFieldDistance(BorderStoneFieldDistanceA)));
	possibleChildren.push_back(new Point(0,-1.0* distances.getStandardFieldDistance(BorderStoneFieldDistanceB)));

	borderstone.searchNeighbourBorderStones(possibleChildren);

	CPPUNIT_ASSERT(borderstone.getAllChildren().front() == Point(0, distances.getStandardFieldDistance(BorderStoneFieldDistanceA))
				   && borderstone.getAllChildren().back() == Point(0,-1* distances.getStandardFieldDistance(BorderStoneFieldDistanceB)));
}
