#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class GetServerInfoCommand : public BaseCommand {
		public:
			GetServerInfoCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}