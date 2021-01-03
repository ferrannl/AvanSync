#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class InfoCommand : public Command {
		public:
			InfoCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}