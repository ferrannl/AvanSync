#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class CreateDirectoryCommand : public BaseCommand {
		public:
			CreateDirectoryCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}