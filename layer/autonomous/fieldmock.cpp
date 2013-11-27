#include "layer/autonomous/fieldmock.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

FieldMock::FieldMock()
{ }

void FieldMock::update()
{ }

const vector<FieldObject>& FieldMock::getAllFieldObjects() const
{
	return m_objects;
}

const vector<Circle>& FieldMock::getAllObstacles() const
{
	return m_obstacles;
}

bool FieldMock::calibratePosition()
{
	return false;
}

void FieldMock::setFieldObjects(const vector<FieldObject> &objects)
{
	m_objects = objects;
}

void FieldMock::setObstacles(const vector<Circle> &obstacles)
{
	m_obstacles = obstacles;
}
