#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/engine.h"
#include "layer/hardware/odometry.h"
#include "common/compare.h"
#include "common/point.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

EngineImpl::EngineImpl(Hardware::Engine &engine, Hardware::Odometry &odometry) :
	m_engine(engine),
	m_odometry(odometry)
{ }

void EngineImpl::goToStraight(const Common::Point &position)
{
	const Point &currentPosition = m_odometry.getCurrentPosition();
	Compare positionCompare(0.05);

	if (positionCompare.isFuzzyEqual(currentPosition, position))
		return;

	Compare angleCompare(0.01);
	Point positionDifference = position - currentPosition;
	double targetOrientation = atan2(positionDifference.getY(), positionDifference.getX());
	double currentOrientation = m_odometry.getCurrentOrientation();

	if (!angleCompare.isFuzzyEqual(currentOrientation, currentOrientation))
		m_engine.setSpeed(0, targetOrientation);
	else
		m_engine.setSpeed(10, targetOrientation);

}
