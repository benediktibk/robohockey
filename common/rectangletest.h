#ifndef ROBOHOCKEY_COMMON_RECTANGLETEST_H
#define ROBOHOCKEY_COMMON_RECTANGLETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class RectangleTest :
			public CPPUNIT_NS::TestFixture
	{
		 CPPUNIT_TEST_SUITE(RectangleTest);
		 CPPUNIT_TEST(constructor_4And5AsOneAnd9And8AsTwo_leftLowerIs4And5);
		 CPPUNIT_TEST(constructor_4And5AsOneAnd9And8AsTwo_rightUpperIs9And8);
		 CPPUNIT_TEST(constructor_9And8AsOneAnd4And5AsTwo_leftLowerIs4And5);
		 CPPUNIT_TEST(constructor_9And8AsOneAnd4And5AsTwo_rightUpperIs9And8);
		 CPPUNIT_TEST(constructor_1And5AsOneAnd4And1AsTwo_leftLowerIs1And1);
		 CPPUNIT_TEST(constructor_1And5AsOneAnd4And1AsTwo_rightUpperIs4And5);
		 CPPUNIT_TEST(isInside_tooMuchLeft_false);
		 CPPUNIT_TEST(isInside_tooMuchRight_false);
		 CPPUNIT_TEST(isInside_tooMuchDown_false);
		 CPPUNIT_TEST(isInside_tooMuchUp_false);
		 CPPUNIT_TEST(isInside_inside_true);
		 CPPUNIT_TEST_SUITE_END();

	private:
		 void constructor_4And5AsOneAnd9And8AsTwo_leftLowerIs4And5();
		 void constructor_4And5AsOneAnd9And8AsTwo_rightUpperIs9And8();
		 void constructor_9And8AsOneAnd4And5AsTwo_leftLowerIs4And5();
		 void constructor_9And8AsOneAnd4And5AsTwo_rightUpperIs9And8();
		 void constructor_1And5AsOneAnd4And1AsTwo_leftLowerIs1And1();
		 void constructor_1And5AsOneAnd4And1AsTwo_rightUpperIs4And5();
		 void isInside_tooMuchLeft_false();
		 void isInside_tooMuchRight_false();
		 void isInside_tooMuchDown_false();
		 void isInside_tooMuchUp_false();
		 void isInside_inside_true();
	};
}
}

#endif
