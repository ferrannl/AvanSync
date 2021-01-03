#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DeleteCommand : public BaseCommand {
		public:
			DeleteCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}