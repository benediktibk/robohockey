#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINE_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINE_H

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class Engine
{
public:
	virtual ~Engine() { }

	virtual void setSpeed(double magnitude, double rotation) = 0;
};
}
}
}

#endif
