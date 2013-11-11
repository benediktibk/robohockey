#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H

#include <opencv2/opencv.hpp>
#include "common/colorType.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObject
	{
	public:
		CameraObject(Common::ColorType color, cv::Rect position);

		cv::Rect getImagePosition() const;
		Common::ColorType getColorType() const;

	private:
		Common::ColorType m_color;
		cv::Rect m_position;
	};
}
}
}

#endif
