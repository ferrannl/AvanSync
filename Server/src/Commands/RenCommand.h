#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class RenCommand : public Command {
		public:
			RenCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}