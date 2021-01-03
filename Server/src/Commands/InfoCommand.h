#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class InfoCommand : public BaseCommand {
		public:
			InfoCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}