#pragma once
#include "../Factories/CommandFactory.h"

namespace Server {
	namespace Controllers {
		class MainController {
		private:
			void run();
			void runCommand(const std::string& command, const std::string& path);
			std::shared_ptr<CommandFactory> _factory;
		public:
			MainController();
		};
	}
}