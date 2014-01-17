#include "layer/autonomous/fielddetectionresulttest.h"
#include "layer/autonomous/fielddetectionresult.h"
#include "common/robotposition.h"
#include <iostream>
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void FieldDetectionResultTest::getTransformationDestination_initWithPoint_pointIs0And0()
{
	RobotPosition position;
	FieldDetectionResult detectionResult(position, 3, false);

	CPPUNIT_ASSERT_EQUAL(position, detectionResult.getTransformationDestination());
}

void FieldDetectionResultTest::getTransformationDestination_initWithPoint_pointIs1And2()
{
	RobotPosition position(Point(1,2), Angle());
	FieldDetectionResult detectionResult(position, 3, false);

	CPPUNIT_ASSERT_EQUAL(position, detectionResult.getTransformationDestination());
}

void FieldDetectionResultTest::isEqualDetectionResult_pointFarAway_FALSE()
{
	RobotPosition position(Point(3,1.54), Angle::getQuarterRotation());
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(1,2), Angle::getFullRotation() *(-1));
	CPPUNIT_ASSERT(!detectionResult.isEqualDetectionResult(testPosition));
}

void FieldDetectionResultTest::isEqualDetectionResult_pointNearButWrongOrientation_FALSE()
{
	RobotPosition position(Point(-1.2,0.9), Angle::getEighthRotation() * 3);
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(-1.18,1), Angle::getThreeQuarterRotation());
	CPPUNIT_ASSERT(!detectionResult.isEqualDetectionResult(testPosition));
}

void FieldDetectionResultTest::isEqualDetectionResult_pointFarButEqualOrientation_FALSE()
{
	RobotPosition position(Point(-1.2,0.9), Angle::getEighthRotation() * 3);
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(2.18,4.6), Angle::getEighthRotation() * 3);
	CPPUNIT_ASSERT(!detectionResult.isEqualDetectionResult(testPosition));
}

void FieldDetectionResultTest::isEqualDetectionResult_pointFuzzyEqual_TRUE()
{
	RobotPosition position(Point(-0.2,2.4), Angle::getHalfRotation() * -(1));
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(-0.18,2.3), Angle::getHalfRotation() * (-1));
	CPPUNIT_ASSERT(detectionResult.isEqualDetectionResult(testPosition));
}

void FieldDetectionResultTest::isEqualDetectionResult_pointGoodOrientationCritical_TRUE()
{
	RobotPosition position(Point(-0.2,2.4), Angle::getHalfRotation());
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(-0.18,2.3), Angle::getHalfRotation() + Angle::getEighthRotation() * 0.2);
	CPPUNIT_ASSERT(detectionResult.isEqualDetectionResult(testPosition));
}

void FieldDetectionResultTest::confirmDetectionResultWithPosition_pointNotGood_noChangesInCounters()
{
	RobotPosition position(Point(3,1.54), Angle::getQuarterRotation());
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(1,2), Angle::getFullRotation() *(-1));
	CPPUNIT_ASSERT(!detectionResult.isEqualDetectionResult(testPosition));

	unsigned int oldNumberOfBorderStones = detectionResult.getNumberOfBorderStones();

	detectionResult.confirmDetectionResultWithPosition(testPosition, 3, true);

	CPPUNIT_ASSERT(!detectionResult.isConfirmedByBothSides());
	CPPUNIT_ASSERT_EQUAL(oldNumberOfBorderStones, detectionResult.getNumberOfBorderStones());
}

void FieldDetectionResultTest::confirmDetectionResultWithPosition_pointGoodAndOnSameSide_notConfirmedButCounterIncreased()
{
	RobotPosition position(Point(3,1.54), Angle::getQuarterRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(3.04,1.6), Angle::getQuarterRotation() *(-1));
	CPPUNIT_ASSERT(detectionResult.isEqualDetectionResult(testPosition));

	unsigned int oldNumberOfBorderStones = detectionResult.getNumberOfBorderStones();

	detectionResult.confirmDetectionResultWithPosition(testPosition, 4, false);

	CPPUNIT_ASSERT(!detectionResult.isConfirmedByBothSides());
	CPPUNIT_ASSERT(oldNumberOfBorderStones < detectionResult.getNumberOfBorderStones());
}

void FieldDetectionResultTest::confirmDetectionResultWithPosition_pointGoodAndOnOtherSide_confirmedAndCounterIncreased()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(-2.2,0.69), Angle::getEighthRotation() *(-1));
	CPPUNIT_ASSERT(detectionResult.isEqualDetectionResult(testPosition));

	unsigned int oldNumberOfBorderStones = detectionResult.getNumberOfBorderStones();

	detectionResult.confirmDetectionResultWithPosition(testPosition, 3, true);

	CPPUNIT_ASSERT(detectionResult.isConfirmedByBothSides());
	CPPUNIT_ASSERT(oldNumberOfBorderStones < detectionResult.getNumberOfBorderStones());
}

void FieldDetectionResultTest::isConfirmedByBothSides_init_FALSE()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, false);

	CPPUNIT_ASSERT(!detectionResult.isConfirmedByBothSides());
}

void FieldDetectionResultTest::isConfirmedByBothSides_confirmFromSameSideOpposite_FALSE()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(-2.2,0.69), Angle::getEighthRotation() *(-1));
	detectionResult.confirmDetectionResultWithPosition(testPosition, 4, true);

	CPPUNIT_ASSERT(!detectionResult.isConfirmedByBothSides());
}

void FieldDetectionResultTest::isConfirmedByBothSides_confirmFromSameSideNear_FALSE()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(-2.2,0.69), Angle::getEighthRotation() *(-1));
	detectionResult.confirmDetectionResultWithPosition(testPosition, 3, false);

	CPPUNIT_ASSERT(!detectionResult.isConfirmedByBothSides());
}

void FieldDetectionResultTest::isConfirmedByBothSides_confirmFromOtherSideOpposite_TRUE()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, false);

	RobotPosition testPosition(Point(-2.2,0.69), Angle::getEighthRotation() *(-1));
	detectionResult.confirmDetectionResultWithPosition(testPosition, 3, true);

	CPPUNIT_ASSERT(detectionResult.isConfirmedByBothSides());
}

void FieldDetectionResultTest::isConfirmedByBothSides_confirmFromOtherSideNear_TRUE()
{
	RobotPosition position(Point(-2.3,0.74), Angle::getEighthRotation() * (-1));
	FieldDetectionResult detectionResult(position, 3, true);

	RobotPosition testPosition(Point(-2.2,0.69), Angle::getEighthRotation() *(-1));
	detectionResult.confirmDetectionResultWithPosition(testPosition, 3, false);

	CPPUNIT_ASSERT(detectionResult.isConfirmedByBothSides());
}


