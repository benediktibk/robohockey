#include "layer/hardware/lidarmock.h"
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;
using namespace std;

LidarMock::LidarMock() :
	m_callsToGetDistance(0),
	m_defaultDistance(10)
{ }

LidarMock::LidarMock(double defaultDistance) :
	m_defaultDistance(defaultDistance)
{ }

double LidarMock::getDistance(unsigned int angle)
{
	assert(angle >= getMinimumSensorNumber());
	assert(angle <= getMaximumSensorNumber());

	++m_callsToGetDistance;

	map<unsigned int, double>::const_iterator value = m_valueForAngle.find(angle);

	if (value == m_valueForAngle.end())
		return m_defaultDistance;
	else
		return value->second;
}

void LidarMock::setValueForAngle(unsigned int angle, double value)
{
	m_valueForAngle[angle] = value;
}

void LidarMock::readSensorDataFromFile(const string &fileName)
{
	ifstream file(fileName.c_str());

	assert(file.is_open());
	while (!file.eof())
	{
		string line;
		char lastCharacter = 'a';

		while (!file.eof() && lastCharacter != '\n')
		{
			file.get(lastCharacter);
			if (lastCharacter != '\n')
				line += lastCharacter;
		}

		stringstream lineStream(line);

		unsigned int sensorNumber;
		double value;
		lineStream >> sensorNumber;
		char buffer[2];
		lineStream.get(buffer, 2);
		lineStream >> value;
		setValueForAngle(sensorNumber, value);
	}
}

unsigned int LidarMock::getCallsToGetDistance() const
{
	return m_callsToGetDistance;
}