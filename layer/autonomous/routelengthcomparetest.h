#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTELENGTHCOMPARETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTELENGTHCOMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouteLengthCompareTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouteLengthCompareTest);
		CPPUNIT_TEST(evaluation_firstOneShorter_true);
		CPPUNIT_TEST(evaulation_secondOneShorter_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void evaluation_firstOneShorter_true();
		void evaulation_secondOneShorter_false();
	};
}
}
}

#endif


