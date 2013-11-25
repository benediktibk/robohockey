#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H

#include <opencv2/opencv.hpp>
#include "common/fieldobjectcolor.h"
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
		CameraObject(Common::FieldObjectColor color, const Common::Point &position);

		Common::Point getPosition() const;
		Common::FieldObjectColor getColor() const;

	private:
		Common::FieldObjectColor m_color;
		Common::Point m_position;
	};
}
}
}

#endif
