#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAMOCK_H

#include "layer/hardware/camera.h"

namespace RoboHockey
{
namespace Layer
{
namespace Hardware
{
	class CameraMock :
			public Camera
	{
	public:
		CameraMock();

		virtual cv::Mat getFrame();
		virtual bool isValid() const;
		unsigned int getCallsToGetFrame() const;

	private:
		unsigned int m_callsToGetFrame;
	};
}
}
}

#endif
