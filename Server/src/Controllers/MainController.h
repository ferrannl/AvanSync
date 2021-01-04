#pragma once
#include <string>
#include <memory>
#include "../Factories/CommandFactory.h"

namespace Server {
	namespace Controllers {
		class MainController : public std::enable_shared_from_this<MainController> {
		public:
			MainController();

			void processCommand(const std::string&, std::string&);
			void run();
		private:
			asio::ip::tcp::iostream _client;
			Factories::CommandFactory _factory;
		};
	}
}