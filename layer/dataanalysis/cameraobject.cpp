#include "layer/dataanalysis/cameraobject.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace cv;

CameraObject::CameraObject(ColorType color, Rect position) :
	m_color(color),
	m_position(position)
{
}

Rect CameraObject::getImagePosition() const
{
	return m_position;
}

ColorType CameraObject::getColorType() const
{
	return m_color;
}
