#include "layer/autonomous/fieldmock.h"

using namespace RoboHockey::Layer::Autonomous;


void FieldMock::update()
{ }

bool FieldMock::tryToFindField()
{
    return false;
}

std::vector<FieldObject> FieldMock::getAllFieldObjects()
{
    return std::vector<FieldObject> ();
}

int FieldMock::achievedGoals()
{
    return 0;
}
