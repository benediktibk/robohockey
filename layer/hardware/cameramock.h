#ifndef ROBOHOCKEY_LAYER_HARDWARE_CAMERAMOCK_H
#define ROBOHOCKEY_LAYER_HARDWARE_CAMERAMOCK_H

#include "layer/hardware/camera.h"
#include <string>

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
		CameraMock(const std::string &filename);
		~CameraMock();

		virtual cv::Mat getFrame() const;
		virtual bool isValid() const;
		virtual void writeDataToFile(const std::string &fileName) const;

		void readDataFromFile(const std::string &fileName);
		void setBlackPicture();

	private:
		cv::Mat *m_testpicture;
	};
}
}
}

#endif
