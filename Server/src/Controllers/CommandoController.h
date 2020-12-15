#pragma once
#include <string>
#include <vector>


namespace
	Controllers {

	class CommandoController {

	private:
		std::vector<std::string> _response;

	public:
		CommandoController();

		void runCommand(const std::string& command);
		void info();
		void dir();
		void get();
		void put();
		void ren();
		void del();
		void mkdir();
		void quit();

		std::vector<std::string> get_response();
	};
}
