#include "watch.h"

using namespace RoboHockey::Common;

Watch::Watch()
{
    restart();
}

double Watch::getTime()
{
    double t=m_start.elapsed();
    return t;
}

void Watch::restart()
{
    m_start.restart();
}
