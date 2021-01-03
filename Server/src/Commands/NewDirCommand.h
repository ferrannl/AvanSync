#pragma once
#include "../Commands/Command.h"

namespace Server {
	namespace Commands {
		class NewDirCommand : public Command {
		public:
			NewDirCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}