#include "layer/autonomous/fieldobject.h"

using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Common;


FieldObject::FieldObject(const Circle &circle, FieldObjectColor color) :
	m_circle(circle),
	m_color(color)
{ }

const Circle &FieldObject::getCircle() const
{
	return m_circle;
}

FieldObjectColor FieldObject::getColor() const
{
	return m_color;
}

void FieldObject::setColor(FieldObjectColor color)
{
	m_color = color;
}

void FieldObject::setCircle(const Circle &circle)
{
	m_circle = circle;
}
