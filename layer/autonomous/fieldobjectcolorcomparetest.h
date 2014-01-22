#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTCOLORCOMPARETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTCOLORCOMPARETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObjectColorCompareTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldObjectColorCompareTest);
		CPPUNIT_TEST(evaluate_yellowAndUnknown_true);
		CPPUNIT_TEST(evaluate_greenAndUnknown_true);
		CPPUNIT_TEST(evaluate_blueAndUnknown_true);
		CPPUNIT_TEST(evaluate_unknownAndYellow_false);
		CPPUNIT_TEST(evaluate_unknownAndBlue_false);
		CPPUNIT_TEST(evaluate_unknownAndGreen_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void evaluate_yellowAndUnknown_true();
		void evaluate_greenAndUnknown_true();
		void evaluate_blueAndUnknown_true();
		void evaluate_unknownAndYellow_false();
		void evaluate_unknownAndBlue_false();
		void evaluate_unknownAndGreen_false();
	};
}
}
}

#endif


