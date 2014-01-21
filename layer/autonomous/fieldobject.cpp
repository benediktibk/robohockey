#include "layer/autonomous/fieldobject.h"
#include <assert.h>

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;

const double FieldObject::m_robotDiameterTreshold = 0.12;
const double FieldObject::m_robotDiameterMaximum = 0.9;
const double FieldObject::m_boundaryPostDiameter = 0.06;
const double FieldObject::m_puckDiameter = 0.12;

FieldObject::FieldObject(const Circle &circle, FieldColor color, unsigned int seenTreshold) :
	m_circle(circle),
	m_color(color),
	m_seen(0),
	m_shouldBeSeen(0),
	m_notSeen(0),
	m_seenTreshold(seenTreshold)
{ }

FieldObject::FieldObject(
		const Circle &circle, FieldColor color, unsigned int seenTreshold,
		unsigned int seen, unsigned int shouldBeSeen, unsigned int notSeen) :
	m_circle(circle),
	m_color(color),
	m_seen(seen),
	m_shouldBeSeen(shouldBeSeen),
	m_notSeen(notSeen),
	m_seenTreshold(seenTreshold)
{ }

const Circle &FieldObject::getCircle() const
{
	return m_circle;
}

FieldColor FieldObject::getColor() const
{
	return m_color;
}

void FieldObject::setColor(FieldColor color)
{
	m_color = color;
}

void FieldObject::setCircle(const Circle &circle)
{
	m_circle = circle;
}

unsigned int FieldObject::getSeen() const
{
	return m_seen;
}

unsigned int FieldObject::getShouldBeSeen() const
{
	return m_shouldBeSeen;
}

unsigned int FieldObject::getNotSeen() const
{
	return m_notSeen;
}

void FieldObject::seen()
{
	++m_seen;
	m_notSeen = 0;
}

void FieldObject::shouldBeSeen()
{
	++m_shouldBeSeen;
}

void FieldObject::notSeen()
{
	++m_notSeen;
}

void FieldObject::cantBeSeen()
{
	m_notSeen = 0;
}

bool FieldObject::isDefinitelyExisting() const
{
	return getShouldBeSeen() >= m_seenTreshold && getSeen() >= m_seenTreshold;
}

bool FieldObject::isMaybeExisting() const
{
	return getShouldBeSeen() >= m_seenTreshold/2 && getSeen() >= m_seenTreshold/2;
}

bool FieldObject::isDefinitelyNotExisting() const
{
	return getNotSeen() >= m_seenTreshold;
}

bool FieldObject::isHardObstacle() const
{
	return m_color == FieldColorGreen || m_circle.getDiameter() > m_robotDiameterTreshold;
}

Circle FieldObject::getObstacle() const
{
	const Point &center = m_circle.getCenter();

	if (m_circle.getDiameter() > m_robotDiameterTreshold)
		return Circle(center, m_robotDiameterMaximum);

	switch(m_color)
	{
	case FieldColorGreen:
		return Circle(center, m_boundaryPostDiameter);
	case FieldColorBlue:
	case FieldColorYellow:
	case FieldColorUnknown:
		return Circle(center, m_puckDiameter);
	}

	assert(false);
	return Circle(); // make the compiler happy
}
