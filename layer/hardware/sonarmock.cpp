#include "layer/hardware/sonarmock.h"
#include <fstream>
#include <assert.h>
#include <sstream>

using namespace std;
using namespace RoboHockey::Layer::Hardware;

SonarMock::SonarMock() :
	m_callsToGetDistanceForSensor(0)
{ }

void SonarMock::updateSensorData()
{ }

double SonarMock::getDistanceForSensor(unsigned int sensorNumber)
{
	++m_callsToGetDistanceForSensor;

	if (m_values.count(sensorNumber) != 0)
		return m_values[sensorNumber];
	else
		return 0;
}

unsigned int SonarMock::getCallsToGetDistanceForSensor() const
{
	return m_callsToGetDistanceForSensor;
}

void SonarMock::setValue(unsigned int sensorNumber, double value)
{
	m_values[sensorNumber] = value;
}

void SonarMock::readSensorDataFromFile(const string &fileName)
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
		setValue(sensorNumber, value);
	}
}
