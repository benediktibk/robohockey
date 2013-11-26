#include "layer/autonomous/fieldmock.h"

using namespace std;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock()
{ }

void FieldMock::update()
{ }

vector<FieldObject> &FieldMock::getAllFieldObjects()
{
	return m_objects;
}

bool FieldMock::calibratePosition()
{
	return false;
}

void FieldMock::setFieldObjects(std::vector<FieldObject> &objects)
{
	m_objects = objects;
}
