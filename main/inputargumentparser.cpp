#include "main/inputargumentparser.h"
#include <assert.h>
#include <sstream>
#include <list>

using namespace RoboHockey::Main;
using namespace std;

InputArgumentParser::InputArgumentParser(const vector<string> &arguments) :
	m_isValid(true),
	m_enableGui(false),
	m_playerServer("localhost"),
	m_angelinaServer("localhost"),
	m_enableRecorder(false),
	m_enableSonar(false)
{
	parse(arguments);
}

bool InputArgumentParser::enableGui() const
{
	assert(isValid());
	return m_enableGui;
}

const string &InputArgumentParser::playerServer() const
{
	assert(isValid());
	return m_playerServer;
}

const string &InputArgumentParser::angelinaServer() const
{
	assert(isValid());
	return m_angelinaServer;
}

bool InputArgumentParser::enableRecorder() const
{
	assert(isValid());
	return m_enableRecorder;
}

const string &InputArgumentParser::recordingPath() const
{
	assert(isValid());
	assert(enableRecorder());
	return m_recordingPath;
}

bool InputArgumentParser::enableSonar() const
{
	assert(isValid());
	return m_enableSonar;
}

bool InputArgumentParser::isValid() const
{
	return m_isValid;
}

string InputArgumentParser::usage() const
{
	stringstream stream;

	stream << "usage: " << endl;
	stream << "All arguments are optional. If a server-IP is not specified localhost is used. By default the gui is disabled." << endl;
	stream << "\t--player <IP>" << endl;
	stream << "\t--angelina <IP>" << endl;
	stream << "\t--enableGui" << endl;
	stream << "\t--recordTo <path>" << endl;

	return stream.str();
}

vector<string> InputArgumentParser::convertArguments(int argc, char **argv)
{
	vector<string> arguments;
	arguments.reserve(argc - 1);

	for (int i = 0; i < argc; ++i)
		arguments.push_back(argv[i]);

	return arguments;
}

void InputArgumentParser::parse(const vector<string> &arguments)
{
	if (arguments.empty())
	{
		m_isValid = false;
		return;
	}

	list<string> argumentsLeft(arguments.begin() + 1, arguments.end());
	bool foundEnableGui = false;
	bool foundAngelina = false;
	bool foundPlayer = false;
	bool foundRecordingPath = false;
	bool foundEnableSonar = false;

	while (!argumentsLeft.empty())
	{
		const string firstArgument = argumentsLeft.front();

		if (firstArgument == "--enableGui")
		{
			if (foundEnableGui)
			{
				m_isValid = false;
				return;
			}

			m_enableGui = true;
			foundEnableGui = true;
		}
		else if (firstArgument == "--player")
		{
			if (argumentsLeft.size() == 1 || foundPlayer)
			{
				m_isValid = false;
				return;
			}

			argumentsLeft.pop_front();
			const string secondArgument = argumentsLeft.front();
			m_playerServer = secondArgument;
			foundPlayer = true;
		}
		else if (firstArgument == "--angelina")
		{
			if (argumentsLeft.size() == 1 || foundAngelina)
			{
				m_isValid = false;
				return;
			}

			argumentsLeft.pop_front();
			const string secondArgument = argumentsLeft.front();
			m_angelinaServer = secondArgument;
			foundAngelina = true;
		}
		else if (firstArgument == "--recordTo")
		{
			if (argumentsLeft.size() == 1 || foundRecordingPath)
			{
				m_isValid = false;
				return;
			}

			argumentsLeft.pop_front();
			const string secondArgument = argumentsLeft.front();
			m_recordingPath = secondArgument;
			m_enableRecorder = true;
			foundRecordingPath = true;
		}
		else if (firstArgument == "--enableSonar")
		{
			if (foundEnableSonar)
			{
				m_isValid = false;
				return;
			}

			m_enableSonar = true;
			foundEnableSonar = true;
		}
		else
		{
			m_isValid = false;
			return;
		}

		argumentsLeft.pop_front();
	}
}
