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
	engine.updateSpeedAndMagnitude();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(1, 1), 0);

	engine.goToStraight(Point(0, 2));
	engine.updateSpeedAndMagnitude();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(Point(1, 1), 0);

	engine.goToStraight(Point(1, -2));
	engine.updateSpeedAndMagnitude();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() < 0);
}
