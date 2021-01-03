#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class DelCommand : public Command {
		public:
			DelCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}