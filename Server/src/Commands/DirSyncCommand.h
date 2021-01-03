#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class DirSyncCommand : public Command {
		public:
			DirSyncCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}