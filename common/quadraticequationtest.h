#ifndef ROBOHOCKEY_COMMON_QUADRATICEQUATIONTEST_H
#define ROBOHOCKEY_COMMON_QUADRATICEQUATIONTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class QuadraticEquationTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(QuadraticEquationTest);
		CPPUNIT_TEST(getSolutions_noRealSolution_resultSizeIs0);
		CPPUNIT_TEST(getSolutions_oneRealSolution_solutionIsCorrect);
		CPPUNIT_TEST(getSolutions_twoRealSolutions_solutionsAreCorrect);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getSolutions_noRealSolution_resultSizeIs0();
		void getSolutions_oneRealSolution_solutionIsCorrect();
		void getSolutions_twoRealSolutions_solutionsAreCorrect();
	};
}
}

#endif


