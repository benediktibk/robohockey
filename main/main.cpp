#include "layer/hardware/robotimpl.h"

using namespace RoboHockey;

int main(int /*argc*/, char **/*argv*/)
{
	Layer::Hardware::Robot *robot = new Layer::Hardware::RobotImpl();
	delete robot;
	return 0;
}
