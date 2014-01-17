#include "layer/strategy/common/colordependentpucktargetfetcher.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

ColorDependentPuckTargetFetcher::ColorDependentPuckTargetFetcher() :
	m_cantReachTargetCounter(0)
{ }

bool ColorDependentPuckTargetFetcher::isCantReachTargetLimitReached() const
{
	if (m_cantReachTargetCounter < 10)
		return false;
	else
		return true;
}

void ColorDependentPuckTargetFetcher::resetCantReachTargetCounter()
{
	m_cantReachTargetCounter = 0;
}

void ColorDependentPuckTargetFetcher::increaseCantReachTargetCounter()
{
	m_cantReachTargetCounter++;
}
