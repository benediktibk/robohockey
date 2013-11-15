#include "layer/dataanalysis/cameraobject.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

CameraObject::CameraObject(ColorType color, const Point &position) :
	m_color(color),
	m_position(position)
{
}

Point CameraObject::getPosition() const
{
	return m_position;
}

ColorType CameraObject::getColorType() const
{
	return m_color;
}
