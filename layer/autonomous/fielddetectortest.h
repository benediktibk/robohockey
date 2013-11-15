#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTORTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldDetectorTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldDetectorTest);
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_true);
		CPPUNIT_TEST(tryToDetectField_5unvalidPoints_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void tryToDetectField_4validFieldPoints_true();
		void tryToDetectField_5unvalidPoints_false();

	};
}
}
}

#endif
