#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/enginemock.h"
#include "layer/hardware/odometrymock.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void EngineTest::goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(1, 2), 0);

	engine.goToStraight(Point(4, 20));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(1, 1), 0);

	engine.goToStraight(Point(0, 2));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(1, 1), 0);

	engine.goToStraight(Point(1, -2));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() < 0);
}

void EngineTest::goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(0, 0), 0);

	engine.goToStraight(Point(-1, 0));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() == 0);
}

void EngineTest::goToStraight_startOrientationCompletelyWrong_lastRotationIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(0, 0), 0);

	engine.goToStraight(Point(-1, 0));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(fabs(hardwareEngine.getLastRotation()) > 0.1);
}
