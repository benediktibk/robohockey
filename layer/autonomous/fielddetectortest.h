#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTORTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDDETECTORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class Compare;
	class LoggerMock;
}
namespace Layer
{
namespace Autonomous
{
	class FieldDetector;
	class FieldDetectorTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldDetectorTest);
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_true);
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_4validFieldPoints_correctRotation);
		CPPUNIT_TEST(tryToDetectField_5invalidPoints_false);
		CPPUNIT_TEST(tryToDetectField_7validPoints_true);
		CPPUNIT_TEST(tryToDetectField_7validPointsOpposite_true);
		CPPUNIT_TEST(tryToDetectField_3pointsFar_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsFarMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsFarMid_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsFarMidMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsMid_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsMidMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsNear_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsNearMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsNearMidMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsNearNearMixed_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsNearMixedMid_correctNewOrigin);
		CPPUNIT_TEST(tryToDetectField_3pointsCorrectDistanceButWrongArragement_false);
		CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

	private:
		void tryToDetectField_4validFieldPoints_true();
		void tryToDetectField_4validFieldPoints_correctNewOrigin();
		void tryToDetectField_4validFieldPoints_correctRotation();
		void tryToDetectField_5invalidPoints_false();
		void tryToDetectField_7validPoints_true();
		void tryToDetectField_7validPointsOpposite_true();
		void tryToDetectField_3pointsFar_correctNewOrigin();
		void tryToDetectField_3pointsFarMixed_correctNewOrigin();
		void tryToDetectField_3pointsFarMid_correctNewOrigin();
		void tryToDetectField_3pointsFarMidMixed_correctNewOrigin();
		void tryToDetectField_3pointsMid_correctNewOrigin();
		void tryToDetectField_3pointsMidMixed_correctNewOrigin();
		void tryToDetectField_3pointsNear_correctNewOrigin();
		void tryToDetectField_3pointsNearMixed_correctNewOrigin();
		void tryToDetectField_3pointsNearMidMixed_correctNewOrigin();
		void tryToDetectField_3pointsNearNearMixed_correctNewOrigin();
		void tryToDetectField_3pointsNearMixedMid_correctNewOrigin();
		void tryToDetectField_3pointsCorrectDistanceButWrongArragement_false();

	private:
		Common::LoggerMock *m_logger;
		FieldDetector *m_fieldDetector;
	};
}
}
}

#endif
