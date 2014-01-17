#include "common/comparetest.h"
#include "common/compare.h"
#include "common/angle.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace std;

void CompareTest::isFuzzyEqual_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyEqual()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(2.0,2.1));
}

void CompareTest::isFuzzyEqual_twoCompletelyEqualVectors_true()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two = one;

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoNearlyEqualVectors_true()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(3.1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoVectorsWithDifferentSize_false()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(3.1);
	two.push_back(1);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoDifferentVectors_false()
{
	Compare compare(0.5);
	vector<double> one;
	vector<double> two;
	one.push_back(4);
	one.push_back(3);
	two.push_back(4);
	two.push_back(2);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_towListsWithRobotPositions_true()
{
	Compare compare(0.1);
	list<RobotPosition> list1, list2;
	list1.push_back(RobotPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 2), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_twoListsWithRobotPositions_false()
{
	Compare compare(0.1);
	list<RobotPosition> list1, list2;
	list1.push_back(RobotPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 3), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_towListsWithRobotPositionsInDiffrentOrder_true()
{
	Compare compare(0.1);
	list<RobotPosition> list1, list2;
	list1.push_back(RobotPosition(Point(1, 2), Angle::getEighthRotation()));
	list1.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 2.5), Angle::getEighthRotation()));
	list2.push_back(RobotPosition(Point(1, 2), Angle::getEighthRotation()));

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(list1, list2));
}

void CompareTest::isFuzzyEqual_twoAnglesNearPi_true()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(179);
	Angle two = Angle::convertFromDegreeToRadiant(181);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesNearZero_true()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(1);
	Angle two = Angle::convertFromDegreeToRadiant(359);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichAreNotEqual_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(90);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichHave90DegreesDifference_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(180);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyEqual_twoAnglesWhichHave270DegreesDifference_false()
{
	Compare compare(0.4);
	Angle one = Angle::convertFromDegreeToRadiant(0);
	Angle two = Angle::convertFromDegreeToRadiant(270);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(one, two));
}

void CompareTest::isFuzzyGreater_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzyGreater()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzyGreater(2.0,2.1));
}

void CompareTest::isFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointTwo_resultIsFuzzySmaller()
{
	Compare compare(0.2);

	CPPUNIT_ASSERT(compare.isFuzzySmaller(2.0,2.1));
}

void CompareTest::isStrictFuzzyGreater_twoPointOneAndTwoAndEpsilonZeroPointZeroFife_resultIsStrictFuzzyGreater()
{
	Compare compare(0.05);

	CPPUNIT_ASSERT(compare.isStrictFuzzyGreater(2.1,2.0));
}

void CompareTest::isStrictFuzzySmaller_towAndTwoPointOneAndEpsilonZeroPointZeroFife_resultIsStrictFuzzySmaller()
{
	Compare compare(0.05);

	CPPUNIT_ASSERT(compare.isStrictFuzzySmaller(2.0,2.1));
}

void CompareTest::isStrictFuzzyGreater_onlyLittleBitGreater_false()
{
	Compare compare(0.1);

	CPPUNIT_ASSERT(!compare.isStrictFuzzyGreater(2.05, 2));
}
