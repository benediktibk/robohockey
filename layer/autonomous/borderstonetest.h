#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_BORDERSTONETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class Point;
}

namespace Layer
{
namespace Autonomous
{
	class BorderStoneTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(BorderStoneTest);
		CPPUNIT_TEST(getNumberOfChildrenRecursive_noChildren_is0);
		CPPUNIT_TEST(getNumberOfChildrenRecursive_twoChildren_is2);
		CPPUNIT_TEST(getDistanceToFather_root_isRoot);
		CPPUNIT_TEST(getDistanceToFather_distanceB_isDistanceB);
		CPPUNIT_TEST(getAllChildren_noValidChildren_isEmpty);
		CPPUNIT_TEST(getAllChildren_2validChildren_has2Entries);
		CPPUNIT_TEST(getAllChildren_2validChildren_correctChildren);
		CPPUNIT_TEST(getPointsOfAllNodesInTree_2validChildren_has3Entries);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void getNumberOfChildrenRecursive_noChildren_is0();
		void getNumberOfChildrenRecursive_twoChildren_is2();
		void getDistanceToFather_root_isRoot();
		void getDistanceToFather_distanceB_isDistanceB();
		void getAllChildren_noValidChildren_isEmpty();
		void getAllChildren_2validChildren_has2Entries();
		void getAllChildren_2validChildren_correctChildren();
		void getPointsOfAllNodesInTree_2validChildren_has3Entries();

	private:
		std::vector<Common::Point*> m_possibleChildren;
	};
}
}
}

#endif
