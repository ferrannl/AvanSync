#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DisconnectCommand : public BaseCommand {
		public:
			DisconnectCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}