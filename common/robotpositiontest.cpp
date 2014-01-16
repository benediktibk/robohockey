#include "common/robotpositiontest.h"
#include "common/robotposition.h"
#include "common/compare.h"
#include <sstream>
#include <math.h>

using namespace RoboHockey::Common;
using namespace std;

void RobotPositionTest::constructor_empty_positionIs0And0()
{
	RobotPosition position;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0, 0), position.getPosition()));
}

void RobotPositionTest::constructor_4And3_positionIs4And3()
{
	RobotPosition position(Point(4, 3), 0);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(4, 3), position.getPosition()));
}

void RobotPositionTest::setPosition_5And6_positionIs5And6()
{
	RobotPosition position;

	position.setPosition(Point(5, 6));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 6), position.getPosition()));
}

void RobotPositionTest::streamOperator_3And2_32()
{
	RobotPosition position(Point(3, 2), 1);
	stringstream stream;

	stream << position;

	CPPUNIT_ASSERT_EQUAL(string("(3, 2, 1)"), stream.str());
}

void RobotPositionTest::operatorMultiply_3And6With2_6And12()
{
	RobotPosition position(Point(3, 6), Angle(-2));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(6, 12), Angle(-2)), position*2));
}

void RobotPositionTest::operatorDivide_3And6With3_1And2()
{
	RobotPosition position(Point(3, 6), Angle(1));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(1, 2), Angle(1)), position/3));
}

void RobotPositionTest::operatorAdd_4And3To5And1_9And4()
{
	RobotPosition positionOne(Point(4, 3), -2);
	RobotPosition positionTwo(Point(5, 1), 1);

	RobotPosition result = positionOne + positionTwo;

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(9, 4), 0), result));
}

void RobotPositionTest::operatorMinus_5And3From9And4_4And1()
{
	RobotPosition positionOne(Point(9, 4), Angle(1));
	RobotPosition positionTwo(Point(5, 3), Angle(-2));

	RobotPosition result = positionOne - positionTwo;

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(4, 1), 0), result));
}

void RobotPositionTest::operatorMultpliyAndAssign_3And5With2_6And10()
{
	RobotPosition position(Point(3, 5), 2);

	position *= 2;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(6, 10), 2), position));
}

void RobotPositionTest::distanceTo_from4And5To8And2_5()
{
	RobotPosition one(Point(4, 5), Angle(3));
	RobotPosition two(Point(8, 2), Angle(-1));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, one.distanceTo(two), 0.00001);
}

void RobotPositionTest::constructor_empty_orientationIs0()
{
	RobotPosition position;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(0), position.getOrientation()));
}


void RobotPositionTest::setOrientation_3_orientationIs3()
{
	RobotPosition position;

	position.setOrientation(Angle(3));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(3), position.getOrientation()));
}

void RobotPositionTest::read_validString_correctValues()
{
	RobotPosition source(Point(1.3, 3.2), Angle(1.1));
	RobotPosition destination;
	stringstream stream;
	stream << source;
	string sourceString = stream.str();

	destination.read(sourceString);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.3, destination.getPosition().getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(3.2, destination.getPosition().getY(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.1, destination.getOrientation().getValueBetweenMinusPiAndPi(), 0.0001);
}

void RobotPositionTest::getRelativeOrientationTo_lookingUpAndTargetInFourthQuarter_correctValue()
{
	RobotPosition source(Point(1, 2), Angle::getQuarterRotation());
	Point point(2, 1);

	Angle result = source.getRelativeOrientationTo(point);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getEighthRotation()*(-3), result));
}

void RobotPositionTest::constructor_orientationIsPi_orientationIsPi()
{
	RobotPosition position(Point(10, 23), Angle(M_PI));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(M_PI), position.getOrientation()));
}
