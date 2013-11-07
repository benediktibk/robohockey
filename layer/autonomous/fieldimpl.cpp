#include "layer/autonomous/fieldimpl.h"
#include "common/robotposition.h"
#include "layer/dataanalysis/odometryimpl.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/dataanalysis/cameraimpl.h"

using namespace RoboHockey::Layer::Autonomous;

FieldImpl::FieldImpl(DataAnalysis::OdometryImpl &odometry, DataAnalysis::LidarImpl &lidar, DataAnalysis::CameraImpl &camera):
	m_odometry(&odometry),
	m_lidar(&lidar),
	m_camera(&camera),
	m_position(new Common::RobotPosition(m_odometry->getCurrentPosition()))
{

}

void FieldImpl::update()
{

}
