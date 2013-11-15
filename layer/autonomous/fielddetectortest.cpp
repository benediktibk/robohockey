#include <vector>
#include "layer/autonomous/fielddetectortest.h"
#include "layer/autonomous/fielddetector.h"
#include "common/point.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void FieldDetectorTest::tryToDetectField_4validFieldPoints_true()
{
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT_EQUAL(result, true);
}

void FieldDetectorTest::tryToDetectField_5unvalidPoints_false()
{
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(4,1.833));
	testPoints.push_back(Point(2,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT_EQUAL(result, false);
}
