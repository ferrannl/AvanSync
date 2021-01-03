#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class GetCommand : public Command {
		public:
			GetCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}