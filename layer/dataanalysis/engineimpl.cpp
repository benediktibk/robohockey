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
	m_odometry(odometry),
	m_enabled(false),
	m_rotationReached(false)
{ }

void EngineImpl::goToStraight(const Common::Point &position)
{
	m_target = position;
	m_enabled = true;
}

void EngineImpl::updateSpeedAndMagnitude()
{
	//! @todo implement a control as we can not rely on the real hardware to do exactly what we want

	if (!m_enabled)
	{
		m_engine.setSpeed(0, 0);
		return;
	}

	Point currentPosition = m_odometry.getCurrentPosition();
	Compare positionCompare(0.05);
	if (positionCompare.isFuzzyEqual(currentPosition, m_target))
	{
		stop();
		return;
	}

	Compare angleCompare(0.05);
	Point positionDifference = m_target - currentPosition;
	double targetOrientation = atan2(positionDifference.getY(), positionDifference.getX());
	double currentOrientation = m_odometry.getCurrentOrientation();

	if (targetOrientation < 0)
		targetOrientation += 2*M_PI;
	if (currentOrientation < 0)
		currentOrientation += 2*M_PI;

	if (angleCompare.isFuzzyEqual(targetOrientation, currentOrientation))
		m_rotationReached = true;

	if (!m_rotationReached)
	{
		double angleDifference = targetOrientation - currentOrientation;
		double rotationSpeed = M_PI/5;
		if ((angleDifference < M_PI && angleDifference > 0) || angleDifference < (-1)*M_PI)
			m_engine.setSpeed(0, rotationSpeed);
		else
			m_engine.setSpeed(0, (-1)*rotationSpeed);
	}
	else
	{
		m_rotationReached = true;
		m_engine.setSpeed(0.5, 0);
	}
}

void EngineImpl::stop()
{
	m_enabled = false;
	m_rotationReached = false;
}
