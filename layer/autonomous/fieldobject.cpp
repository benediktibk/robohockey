#include "layer/autonomous/fieldobject.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;


FieldObject::FieldObject(const Circle &circle, FieldColor color) :
	m_circle(circle),
	m_color(color),
	m_seen(0),
	m_shouldBeSeen(0),
	m_notSeen(0)
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

bool FieldObject::isDefinitelyExisting() const
{
	return getShouldBeSeen() >= 2 && getSeen() >= 2;
}

bool FieldObject::isDefinitelyNotExisting() const
{
	return getNotSeen() >= 2;
}
