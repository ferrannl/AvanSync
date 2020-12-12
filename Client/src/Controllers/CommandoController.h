#pragma once
#include <string>

namespace
	Controllers {

	class CommandoController {

	private:

	public:
		CommandoController();

		void runCommand(std::string command);
		void info();
		void dir();
		void get();
		void put();
		void ren();
		void del();
		void mkdir();
		void quit();
	};
}
