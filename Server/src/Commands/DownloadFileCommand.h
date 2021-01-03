#pragma once
#include "../Commands/BaseCommand.h"

namespace Server {
	namespace Commands {
		class DownloadFileCommand : public BaseCommand {
		public:
			DownloadFileCommand(std::shared_ptr<Controllers::MainController>);

			void execute(asio::ip::tcp::iostream&, const std::string & = "");
		};
	}
}