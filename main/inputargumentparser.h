#ifndef ROBOHOCKEY_MAIN_INPUTARGUMENTPARSER_H
#define ROBOHOCKEY_MAIN_INPUTARGUMENTPARSER_H

#include <string>
#include <vector>

namespace RoboHockey
{
namespace Main
{
class InputArgumentParser
{
	public:
		InputArgumentParser(const std::vector<std::string> &arguments);

		bool enableGui() const;
		const std::string& playerServer() const;
		const std::string& angelinaServer() const;
		bool isValid() const;
		std::string usage() const;

		static std::vector<std::string> convertArguments(int argc, char **argv);

	private:
		void parse(const std::vector<std::string> &arguments);

	private:
		bool m_isValid;
		bool m_enableGui;
		std::string m_playerServer;
		std::string m_angelinaServer;
	};
}
}

#endif


