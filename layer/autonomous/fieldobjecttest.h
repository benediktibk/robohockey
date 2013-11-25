#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDOBJECTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldObjectTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldObjectTest);
		CPPUNIT_TEST(constructor_validCircle_getCircleReturnsSameCircle);
		CPPUNIT_TEST(constructor_validColor_getCircleReturnsSameColor);
		CPPUNIT_TEST(setColor_blueColor_IsBlueColor);
		CPPUNIT_TEST(setCircle_validCircle_getCircleReturnsSameCircle);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_validCircle_getCircleReturnsSameCircle();
		void constructor_validColor_getCircleReturnsSameColor();
		void setColor_blueColor_IsBlueColor();
		void setCircle_validCircle_getCircleReturnsSameCircle();
	};
}
}
}

#endif
