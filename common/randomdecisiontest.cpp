#include "common/randomdecisiontest.h"
#include "common/randomdecision.h"
#include <stdlib.h>

using namespace RoboHockey::Common;

void RandomDecisionTest::decide_possibility0_false()
{
	RandomDecision decision(0);

	CPPUNIT_ASSERT(!decision.decide());
}

void RandomDecisionTest::decide_possibility1_true()
{
	RandomDecision decision(1);

	CPPUNIT_ASSERT(decision.decide());
}

void RandomDecisionTest::decide_called1000TimesAndPossibilityAHalf_around500TimesTrue()
{
	RandomDecision decision(0.5);
	unsigned int trueCount = 0;

	srand(5);

	for (unsigned int i = 0; i < 1000; ++i)
		if (decision.decide())
			++trueCount;

	CPPUNIT_ASSERT(450 < trueCount && trueCount < 550);
}
