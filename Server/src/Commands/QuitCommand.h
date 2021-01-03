#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class QuitCommand : public Command {
		public:
			QuitCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}