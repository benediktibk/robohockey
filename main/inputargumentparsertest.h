#ifndef ROBOHOCKEY_MAIN_INPUTARGUMENTPARSERTEST_H
#define ROBOHOCKEY_MAIN_INPUTARGUMENTPARSERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Main
{
	class InputArgumentParserTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(InputArgumentParserTest);
		CPPUNIT_TEST(constructor_noArguments_invalid);
		CPPUNIT_TEST(constructor_oneArgument_validAndSettingsCorrect);
		CPPUNIT_TEST(constructor_onlyEnableGui_validAndSettingsCorrect);
		CPPUNIT_TEST(constructor_onlyAngelinaServer_validAndSettingsCorrect);
		CPPUNIT_TEST(constructor_onlyPlayerServer_validAndSettingsCorrect);
		CPPUNIT_TEST(constructor_enableGuiTwice_invalid);
		CPPUNIT_TEST(constructor_angelinaTwice_invalid);
		CPPUNIT_TEST(constructor_playerTwice_invalid);
		CPPUNIT_TEST(constructor_everythingSet_validAndSettingsCorrect);
		CPPUNIT_TEST(constructor_ipOfAngelinaMissing_invalid);
		CPPUNIT_TEST(constructor_ipOfPlayerMissing_invalid);
		CPPUNIT_TEST(constructor_wrongArgument_invalid);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_noArguments_invalid();
		void constructor_oneArgument_validAndSettingsCorrect();
		void constructor_onlyEnableGui_validAndSettingsCorrect();
		void constructor_onlyAngelinaServer_validAndSettingsCorrect();
		void constructor_onlyPlayerServer_validAndSettingsCorrect();
		void constructor_enableGuiTwice_invalid();
		void constructor_angelinaTwice_invalid();
		void constructor_playerTwice_invalid();
		void constructor_everythingSet_validAndSettingsCorrect();
		void constructor_ipOfAngelinaMissing_invalid();
		void constructor_ipOfPlayerMissing_invalid();
		void constructor_wrongArgument_invalid();
	};
}
}

#endif


