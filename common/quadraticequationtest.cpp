#include "common/quadraticequationtest.h"
#include "common/quadraticequation.h"
#include "common/compare.h"
#include <algorithm>

using namespace std;
using namespace RoboHockey::Common;

void QuadraticEquationTest::getSolutions_noRealSolution_resultSizeIs0()
{
	QuadraticEquation equation(1, 1.5, 2);
	Compare compare(0.0001);

	vector<double> result = equation.getSolutions(compare);

	CPPUNIT_ASSERT_EQUAL((size_t)0, result.size());
}

void QuadraticEquationTest::getSolutions_oneRealSolution_solutionIsCorrect()
{
	QuadraticEquation equation(2, 3, 9.0/8);
	Compare compare(0.0001);

	vector<double> result = equation.getSolutions(compare);

	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-3.0/(2*2), result.front(), 0.0001);
}

void QuadraticEquationTest::getSolutions_twoRealSolutions_solutionsAreCorrect()
{
	QuadraticEquation equation(2, 3, 1);
	Compare compare(0.0001);

	vector<double> result = equation.getSolutions(compare);

	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
	double smallSolution = min(result[0], result[1]);
	double bigSolution = max(result[0], result[1]);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1, smallSolution, 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.5, bigSolution, 0.0001);
}
