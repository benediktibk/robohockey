#include "common/randomdecision.h"
#include <assert.h>
#include <stdlib.h>

using namespace RoboHockey::Common;

RandomDecision::RandomDecision(double possibilityForTrue) :
	m_possibilityForTrue(possibilityForTrue)
{
	assert(possibilityForTrue >= 0 && possibilityForTrue <= 1);
}

bool RandomDecision::decide() const
{
	int randomNumber = rand();
	double randomNumberInRange = static_cast<double>(randomNumber)/RAND_MAX;

	if (randomNumberInRange <= m_possibilityForTrue)
		return true;
	else
		return false;
}
