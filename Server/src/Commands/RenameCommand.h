#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class RenameCommand : public BaseCommand {
		public:
			RenameCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}