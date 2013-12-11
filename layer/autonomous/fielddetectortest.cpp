#include <vector>
#include "layer/autonomous/fielddetectortest.h"
#include "layer/autonomous/fielddetector.h"
#include "common/point.h"
#include <math.h>
#include <assert.h>

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

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
}

void FieldDetectorTest::tryToDetectField_4validFieldPoints_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}

void FieldDetectorTest::tryToDetectField_4validFieldPoints_correctRotation()
{
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.5*M_PI, fieldDetector.getRotation(), 0.001);
}

void FieldDetectorTest::tryToDetectField_5invalidPoints_false()
{
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(4,1.833));
	testPoints.push_back(Point(2,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(!result);
}

void FieldDetectorTest::tryToDetectField_7validPoints_true()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,-0.666));
	testPoints.push_back(Point(1,-0.25));
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));
	testPoints.push_back(Point(1,4.333));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}

void FieldDetectorTest::tryToDetectField_3pointsFar_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));
	testPoints.push_back(Point(1,4.333));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}

void FieldDetectorTest::tryToDetectField_3pointsFarMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,3.916));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,4.333));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsFarMid_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));
	testPoints.push_back(Point(1,3.916));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsFarMidMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,3.916));
	testPoints.push_back(Point(1,2.666));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsMid_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,2.666));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsMidMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1.833));
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,2.666));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsNear_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,-0.25));
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,1.833));
	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}

void FieldDetectorTest::tryToDetectField_3pointsNearMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,-0.666));
	testPoints.push_back(Point(1,-0.25));
	testPoints.push_back(Point(1,1));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));

}

void FieldDetectorTest::tryToDetectField_3pointsNearMidMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,1));
	testPoints.push_back(Point(1,-0.25));
	testPoints.push_back(Point(1,1.833));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}

void FieldDetectorTest::tryToDetectField_3pointsNearNearMixed_correctNewOrigin()
{
	Compare compare(0.01);
	vector<Point> testPoints;
	testPoints.push_back(Point(1,-0.25));
	testPoints.push_back(Point(1,-0.666));
	testPoints.push_back(Point(1,1));

	FieldDetector fieldDetector(Point(), testPoints);
	bool result = fieldDetector.tryToDetectField();

	CPPUNIT_ASSERT(result);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1-(1.25+0.416)), fieldDetector.getNewOrigin()));
}
