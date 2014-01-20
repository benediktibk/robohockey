#include "main/inputargumentparsertest.h"
#include "main/inputargumentparser.h"

using namespace RoboHockey::Main;
using namespace std;

void InputArgumentParserTest::constructor_noArguments_invalid()
{
	vector<string> arguments;

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_oneArgument_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.playerServer());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.angelinaServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_onlyEnableGui_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--enableGui");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.playerServer());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.angelinaServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_onlyAngelinaServer_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--angelina");
	arguments.push_back("127.0.0.1");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.playerServer());
	CPPUNIT_ASSERT_EQUAL(string("127.0.0.1"), parser.angelinaServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_onlyPlayerServer_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--player");
	arguments.push_back("127.0.0.1");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.angelinaServer());
	CPPUNIT_ASSERT_EQUAL(string("127.0.0.1"), parser.playerServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_enableGuiTwice_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--enableGui");
	arguments.push_back("--enableGui");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_angelinaTwice_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--angelina");
	arguments.push_back("127.0.0.1");
	arguments.push_back("--angelina");
	arguments.push_back("127.0.0.2");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_playerTwice_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--player");
	arguments.push_back("127.0.0.1");
	arguments.push_back("--player");
	arguments.push_back("127.0.0.2");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_everythingSet_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--enableGui");
	arguments.push_back("--player");
	arguments.push_back("127.0.0.1");
	arguments.push_back("--angelina");
	arguments.push_back("127.0.0.2");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("127.0.0.2"), parser.angelinaServer());
	CPPUNIT_ASSERT_EQUAL(string("127.0.0.1"), parser.playerServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_ipOfAngelinaMissing_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--player");
	arguments.push_back("127.0.0.1");
	arguments.push_back("--angelina");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_ipOfPlayerMissing_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--angelina");
	arguments.push_back("127.0.0.1");
	arguments.push_back("--player");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_wrongArgument_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("BLOB");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_recordingPathSet_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--recordTo");
	arguments.push_back("BLOB");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.playerServer());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.angelinaServer());
	CPPUNIT_ASSERT(parser.enableRecorder());
	CPPUNIT_ASSERT_EQUAL(string("BLOB"), parser.recordingPath());
	CPPUNIT_ASSERT(!parser.enableSonar());
}

void InputArgumentParserTest::constructor_recordingPathSetTwice_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--recordTo");
	arguments.push_back("BLOB");
	arguments.push_back("--recordTo");
	arguments.push_back("blob");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_enableSonarOnce_validAndSettingsCorrect()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--enableSonar");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.enableGui());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.angelinaServer());
	CPPUNIT_ASSERT_EQUAL(string("localhost"), parser.playerServer());
	CPPUNIT_ASSERT(!parser.enableRecorder());
	CPPUNIT_ASSERT(parser.enableSonar());
}

void InputArgumentParserTest::constructor_enableSonarTwice_invalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--enableSonar");
	arguments.push_back("--enableSonar");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}
