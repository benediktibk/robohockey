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
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_correctRotation);
		CPPUNIT_TEST(tryToDetectField_5invalidPoints_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void tryToDetectField_4validFieldPoints_true();
		void tryToDetectField_4validFieldPoints_correctNewOrigin();
		void tryToDetectField_4validFieldPoints_correctRotation();
		void tryToDetectField_5invalidPoints_false();


	};
}
}
}

#endif
