#include "layer/dataanalysis/lidarobject.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

LidarObject::LidarObject()
{ }

LidarObject::LidarObject(const Point &position, double diameter) :
	Circle(position, diameter)
{ }