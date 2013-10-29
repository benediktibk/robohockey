#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERA_H

namespace cv
{
class Mat;
}

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class Camera
{
public:
	virtual ~Camera() { }

	virtual void getColor() const;
};
}
}
}

#endif
