#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAR_H

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class Lidar
{
public:
	virtual ~Lidar() { }

	virtual void getAllObjects() const = 0;
	//Shouldn't be void but Vector of Object/Obstacle-Classes
};
}
}
}

#endif
