#pragma once
#include <string>

namespace
	Controllers {

	class CommandoController {

	private:
		std::string _response;

	public:
		CommandoController();

		std::string runCommand(const std::string& command);
		std::string info();
		std::string dir();
		std::string get();
		std::string put();
		std::string ren();
		std::string del();
		std::string mkdir();
		std::string quit();
	};
}
