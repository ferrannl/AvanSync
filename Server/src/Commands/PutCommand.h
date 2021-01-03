#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class PutCommand : public Command {
		public:
			PutCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}