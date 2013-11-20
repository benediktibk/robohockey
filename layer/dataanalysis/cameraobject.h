#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H

#include <opencv2/opencv.hpp>
#include "layer/dataanalysis/colortype.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class CameraObject
	{
	public:
		CameraObject(ColorType color, const Common::Point &position);

		Common::Point getPosition() const;
		ColorType getColorType() const;

	private:
		ColorType m_color;
		Common::Point m_position;
	};
}
}
}

#endif
