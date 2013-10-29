#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERASTUB_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERASTUB_H

#include "layer/dataanalysis/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class CameraStub :
		public Camera
{
public:
	virtual void getColor() const;
};
}
}
}

#endif
