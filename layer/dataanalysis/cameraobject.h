#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H

#include <opencv2/opencv.hpp>
#include "layer/dataanalysis/colorType.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObject
	{
	public:
		CameraObject(ColorType color, cv::Rect position);

		cv::Rect getImagePosition() const;
		ColorType getColorType() const;

	private:
		ColorType m_color;
		cv::Rect m_position;
	};
}
}
}

#endif
