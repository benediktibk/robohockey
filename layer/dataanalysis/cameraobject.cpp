#include "layer/dataanalysis/cameraobject.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

CameraObject::CameraObject(FieldColor color, const Point &position) :
	m_color(color),
	m_position(position)
{ }

Point CameraObject::getPosition() const
{
	return m_position;
}

FieldColor CameraObject::getColor() const
{
	return m_color;
}
