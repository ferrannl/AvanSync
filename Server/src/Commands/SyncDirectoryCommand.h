#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class SyncDirectoryCommand : public BaseCommand {
		public:
			SyncDirectoryCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}