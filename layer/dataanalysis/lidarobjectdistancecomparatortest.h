#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTDISTANCECOMPARATORTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTDISTANCECOMPARATORTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObjectDistanceComparatorTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarObjectDistanceComparatorTest);
		CPPUNIT_TEST(operator_firstOneCloser_true);
		CPPUNIT_TEST(operator_secondOneCloser_false);
		CPPUNIT_TEST(operator_firstOneThrougBigDiameterCloser_true);
		CPPUNIT_TEST(operator_secondOneThrougBidDiameterCloser_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void operator_firstOneCloser_true();
		void operator_secondOneCloser_false();
		void operator_firstOneThrougBigDiameterCloser_true();
		void operator_secondOneThrougBidDiameterCloser_false();
	};
}
}
}

#endif
