#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERAOBJECT_H

#include <opencv2/opencv.hpp>
#include "common/fieldcolor.h"
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
		CameraObject(Common::FieldColor color, const Common::Point &position);

		Common::Point getPosition() const;
		Common::FieldColor getColor() const;

	private:
		Common::FieldColor m_color;
		Common::Point m_position;
	};
}
}
}

#endif
