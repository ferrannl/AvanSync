#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class PutCommand : public BaseCommand {
		public:
			PutCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}