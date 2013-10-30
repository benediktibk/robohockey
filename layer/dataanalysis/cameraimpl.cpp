#include "layer/dataanalysis/cameraimpl.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

CameraImpl::CameraImpl(const Hardware::Camera &camera) :
	m_camera(camera)
{ }

void CameraImpl::getColor() const
{ }
