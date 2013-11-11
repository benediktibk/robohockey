#include "common/robotpositiontest.h"
#include "common/robotposition.h"
#include "common/compare.h"
#include <sstream>

using namespace RoboHockey::Common;

void RobotPositionTest::constructor_empty_xIs0()
{
	RobotPosition position;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, position.getX(), 0.0001);
}

void RobotPositionTest::constructor_empty_yIs0()
{
	RobotPosition position;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, position.getY(), 0.0001);
}

void RobotPositionTest::constructor_xIs4_xIs4()
{
	RobotPosition position(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, position.getX(), 0.0001);
}

void RobotPositionTest::constructor_yIs6_yIs6()
{
	RobotPosition position(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, position.getY(), 0.0001);
}

void RobotPositionTest::setX_5_xIs5()
{
	RobotPosition position;

	position.setX(5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, position.getX(), 0.0001);
}

void RobotPositionTest::setY_4_yIs4()
{
	RobotPosition position;

	position.setY(4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, position.getY(), 0.0001);
}

void RobotPositionTest::streamOperator_3And2_32()
{
	RobotPosition position(3, 2);
	std::stringstream stream;

	stream << position;

	CPPUNIT_ASSERT_EQUAL(std::string("(3, 2)"), stream.str());
}

void RobotPositionTest::operatorMultiply_3And6With2_6And12()
{
	RobotPosition position(3, 6);

	CPPUNIT_ASSERT_EQUAL(RobotPosition(6, 12), position*2);
}

void RobotPositionTest::operatorDivide_3And6With3_1And2()
{
	RobotPosition position(3, 6);

	CPPUNIT_ASSERT_EQUAL(RobotPosition(1, 2), position/3);
}

void RobotPositionTest::operatorAdd_4And3To5And1_9And4()
{
	RobotPosition positionOne(4, 3);
	RobotPosition positionTwo(5, 1);

	RobotPosition result = positionOne + positionTwo;

	CPPUNIT_ASSERT_EQUAL(RobotPosition(9, 4), result);
}

void RobotPositionTest::operatorMinus_5And3From9And4_4And1()
{
	RobotPosition positionOne(9, 4);
	RobotPosition positionTwo(5, 3);

	RobotPosition result = positionOne - positionTwo;

	CPPUNIT_ASSERT_EQUAL(RobotPosition(4, 1), result);
}

void RobotPositionTest::operatorMultpliyAndAssign_3And5With2_6And10()
{
	RobotPosition position(3, 5);

	position *= 2;

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(6, 10), position));
}

void RobotPositionTest::distanceTo_from4And5To8And2_5()
{
	RobotPosition one(4, 5);
	RobotPosition two(8, 2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, one.distanceTo(two), 0.00001);
}

void RobotPositionTest::constructor_empty_orientationIs0()
{
	RobotPosition position;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, position.getOrientation(), 0.00001);
}


void RobotPositionTest::setOrientation_76_orientationIs76()
{
	RobotPosition position;
	position.setOrientation(76);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(76, position.getOrientation(), 0.00001);
}


void RobotPositionTest::constructor_orientationIs120_orientationIs120()
{
	RobotPosition position(10,23,120);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(120, position.getOrientation(), 0.00001);
}
