#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAMOCK_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAMOCK_H

#include "layer/dataanalysis/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraMock :
			public Camera
	{
	public:
		virtual void getColor() const;
	};
}
}
}

#endif
