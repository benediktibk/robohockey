#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERASTUB_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERASTUB_H

#include "layer/hardware/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class CameraStub :
			public Camera
	{
	public:
		virtual cv::Mat getFrame();
		virtual bool isValid() const;
	};
}
}
}

#endif
