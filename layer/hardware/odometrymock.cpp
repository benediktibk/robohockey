#include "layer/hardware/odometrymock.h"
#include "common/point.h"
#include <fstream>
#include <sstream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Hardware;
using namespace std;

OdometryMock::OdometryMock() :
	m_callsToSetCurrentPosition(0)
{ }

void OdometryMock::setCurrentPosition(const RobotPosition &position)
{
	++m_callsToSetCurrentPosition;
	m_currentPosition = position;
}

RobotPosition OdometryMock::getCurrentPosition() const
{
	return m_currentPosition;
}

void OdometryMock::writeDataToFile(const string &) const
{ }

unsigned int OdometryMock::getCallsToSetCurrentPosition() const
{
	return m_callsToSetCurrentPosition;
}

void OdometryMock::readDataFromFile(const string &fileName)
{
	fstream file(fileName.c_str(), ios::in);
	string content;
	file >> content;
	m_currentPosition.read(content);
	file.close();
}
