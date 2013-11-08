#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/cameramock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void CameraTest::getCameraObject_mockHardwareCamera_atLeastOneCallToGetFrame()
{
	Hardware::CameraMock hardwareCamera;
	CameraImpl camera(hardwareCamera);

	camera.getCameraObject();

	CPPUNIT_ASSERT(hardwareCamera.getCallsToGetFrame() > 0);
}

